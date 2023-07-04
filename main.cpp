//
// Created by Aleksis Toren on 03.07.2023.
//

#include <fstream>
#include <iostream>
#include <cstdint>
#include <vector>
#include <iomanip>
#include "parser/PcapParser.h"
#include "decoder/parts/MarketDataPacketHeader.h"
#include "decoder/parts/SBEHeader.h"
#include "decoder/parts/RepeatingGroupDimensions.h"
#include "decoder/parts/RootBlock.h"
#include "decoder/parts/GroupBlock.h"
#include "decoder/parts/IncrementalPacketHeader.h"

const std::string PCAP_FILE_PATH = "/Users/aleksistoren/Downloads/2023-04-25.1849-1906.pcap";

// A utility function to convert binary data to the desired type
template <typename T>
T fromBinary(const std::vector<uint8_t>::const_iterator &begin) {
    T value = 0;
    for (int i = 0; i < sizeof(T); i++) {
        value |= (T)(*(begin + i)) << (8 * i);
    }
    return value;
}

void decodeSnapshot(const std::vector<uint8_t> &data) {
    auto it = data.cbegin();

    if (data.size() < sizeof(MarketDataPacketHeader) + sizeof(SBEHeader) + sizeof(RepeatingGroupDimensions)) {
        std::cout << "Data is too short to contain a valid message.\n";
        return;
    }

    MarketDataPacketHeader marketDataPacketHeader;
    marketDataPacketHeader.MsgSeqNum = fromBinary<uint32_t>(it); it += 4;
    std::cout << "MsgSeqNum: " << marketDataPacketHeader.MsgSeqNum << "\n";

    marketDataPacketHeader.MsgSize = fromBinary<uint16_t>(it); it += 2;
    std::cout << "MsgSize: " << marketDataPacketHeader.MsgSize << "\n";

    marketDataPacketHeader.MsgFlags = fromBinary<uint16_t>(it); it += 2;
    std::cout << "MsgFlags: " << marketDataPacketHeader.MsgFlags << "\n";

    marketDataPacketHeader.SendingTime = fromBinary<uint64_t>(it); it += 8;
    std::cout << "SendingTime: " << marketDataPacketHeader.SendingTime << "\n";

    SBEHeader sbeHeader;
    sbeHeader.BlockLength = fromBinary<uint16_t>(it); it += 2;
    std::cout << "BlockLength: " << sbeHeader.BlockLength << "\n";

    sbeHeader.TemplateID = fromBinary<uint16_t>(it); it += 2;
    std::cout << "TemplateID: " << sbeHeader.TemplateID << "\n";

    sbeHeader.SchemaID = fromBinary<uint16_t>(it); it += 2;
    std::cout << "SchemaID: " << sbeHeader.SchemaID << "\n";

    sbeHeader.Version = fromBinary<uint16_t>(it); it += 2;
    std::cout << "Version: " << sbeHeader.Version << "\n";

    if (std::distance(it, data.cend()) < sbeHeader.BlockLength) {
        std::cout << "Data is too short to contain a valid root block.\n";
        return;
    }

    RootBlock rootBlock;
    rootBlock.data.insert(rootBlock.data.end(), it, it + sbeHeader.BlockLength);
    it += sbeHeader.BlockLength;
    std::cout << "Root block data size: " << rootBlock.data.size() << "\n";

    if (std::distance(it, data.cend()) < sizeof(RepeatingGroupDimensions)) {
        std::cout << "Data is too short to contain valid repeating group dimensions.\n";
        return;
    }

    RepeatingGroupDimensions repeatingGroupDimensions;
    repeatingGroupDimensions.blockLength = fromBinary<uint16_t>(it); it += 2;
    std::cout << "Repeating group block length: " << repeatingGroupDimensions.blockLength << "\n";

    repeatingGroupDimensions.numInGroup = fromBinary<uint8_t>(it); it += 1;
    std::cout << "Number in group: " << (int)repeatingGroupDimensions.numInGroup << "\n";

    if (std::distance(it, data.cend()) < repeatingGroupDimensions.numInGroup * repeatingGroupDimensions.blockLength) {
        std::cout << "Data is too short to contain all group blocks.\n";
        return;
    }

    for (uint8_t i = 0; i < repeatingGroupDimensions.numInGroup; i++) {
        GroupBlock groupBlock;
        groupBlock.data.insert(groupBlock.data.end(), it, it + repeatingGroupDimensions.blockLength);
        it += repeatingGroupDimensions.blockLength;
        std::cout << "Group block #" << (int)i << " data size: " << groupBlock.data.size() << "\n";
    }
}

void decodeIncremental(const std::vector<uint8_t> &data) {
    auto it = data.cbegin();

    MarketDataPacketHeader marketDataPacketHeader;
    marketDataPacketHeader.MsgSeqNum = fromBinary<uint32_t>(it);
    it += 4;
    std::cout << "MsgSeqNum: " << marketDataPacketHeader.MsgSeqNum << "\n";

    marketDataPacketHeader.MsgSize = fromBinary<uint16_t>(it);
    it += 2;
    std::cout << "MsgSize: " << marketDataPacketHeader.MsgSize << "\n";

    marketDataPacketHeader.MsgFlags = fromBinary<uint16_t>(it);
    it += 2;
    std::cout << "MsgFlags: " << marketDataPacketHeader.MsgFlags << "\n";

    marketDataPacketHeader.SendingTime = fromBinary<uint64_t>(it);
    it += 8;
    std::cout << "SendingTime: " << marketDataPacketHeader.SendingTime << "\n";

    IncrementalPacketHeader incrementalPacketHeader;
    incrementalPacketHeader.TransactTime = fromBinary<uint64_t>(it);
    it += 8;
    std::cout << "TransactTime: " << incrementalPacketHeader.TransactTime << "\n";

    incrementalPacketHeader.TradingSessionID = fromBinary<uint32_t>(it);
    it += 4;
    std::cout << "TradingSessionID: " << incrementalPacketHeader.TradingSessionID << "\n";

    // Loop for handling repeated SBEHeader-RootBlock pairs
    while (it != data.cend()) {
        SBEHeader sbeHeader;
        sbeHeader.BlockLength = fromBinary<uint16_t>(it);
        it += 2;
        std::cout << "BlockLength: " << sbeHeader.BlockLength << "\n";

        sbeHeader.TemplateID = fromBinary<uint16_t>(it);
        it += 2;
        std::cout << "TemplateID: " << sbeHeader.TemplateID << "\n";

        sbeHeader.SchemaID = fromBinary<uint16_t>(it);
        it += 2;
        std::cout << "SchemaID: " << sbeHeader.SchemaID << "\n";

        sbeHeader.Version = fromBinary<uint16_t>(it);
        it += 2;
        std::cout << "Version: " << sbeHeader.Version << "\n";

        if (std::distance(it, data.cend()) < sbeHeader.BlockLength) {
            std::cout << "Data is too short to contain a valid root block.\n";
            return;
        }

        RootBlock rootBlock;
        rootBlock.data.insert(rootBlock.data.end(), it, it + sbeHeader.BlockLength);
        it += sbeHeader.BlockLength;
        std::cout << "Root block data size: " << rootBlock.data.size() << "\n";
        // Log the root block data
        std::cout << "Root block data: ";
        for (auto byte : rootBlock.data) {
            std::cout << static_cast<int>(byte) << " ";
        }
        std::cout << "\n";

    }
}


int main() {
    // Open the pcap file
    std::ifstream file(PCAP_FILE_PATH, std::ios::binary);
    PcapParser parser = PcapParser(PCAP_FILE_PATH);

    auto res = parser.parse();

    for (const auto& i:res){
        decodeIncremental(i.packetData);
    }

    return 0;
}
