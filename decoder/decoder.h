//
// Created by Aleksis Toren on 04.07.2023.
//

#include "parts/SBEHeader.h"
#include "parts/RootBlock.h"
#include "parts/IncrementalPacketHeader.h"
#include "parts/RepeatingGroupDimensions.h"
#include "parts/MarketDataPacketHeader.h"

#ifndef PARSERENCODER_DECODER_H
#define PARSERENCODER_DECODER_H

#endif //PARSERENCODER_DECODER_H


class Decoder {
public:
    static void decode(const std::vector<uint8_t> &data) {
        auto it = data.cbegin();

        it = decodeMarketDataPacketHeader(it, data);

        if (it == data.cend()) {
            std::cout << "MarketDataPacketHeader could not be decoded.\n";
            return;
        }

        if (!decodeSnapshot(it, data)) {
            std::cout << "Snapshot decoding failed. Trying incremental decoding...\n";
            it = data.cbegin();  // Reset the iterator to the beginning
            it = decodeMarketDataPacketHeader(it, data);  // Decode the header again for incremental
            if (!decodeIncremental(it, data)) {
                std::cout << "Both snapshot and incremental decoding failed.\n";
            }
        }
    }

private:
    // Other private methods remain the same...

    static bool decodeSnapshot(std::vector<uint8_t>::const_iterator &it, const std::vector<uint8_t> &data) {
        // If decoding fails at any point, return false.
        // Otherwise, return true.

        SBEHeader sbeHeader;
        sbeHeader = decodeSBEHeader(it, data);
        if (it == data.cend()) return false;

        if (std::distance(it, data.cend()) < sbeHeader.BlockLength) {
            std::cout << "Data is too short to contain a valid root block.\n";
            return false;
        }

        // Assume RootBlock's decode method fills the data and updates the iterator
        RootBlock rootBlock;
        rootBlock.data.insert(rootBlock.data.end(), it, it + sbeHeader.BlockLength);
        it += sbeHeader.BlockLength;

        RepeatingGroupDimensions repeatingGroupDimensions;
        repeatingGroupDimensions = decodeRepeatingGroupDimensions(it, data);
        if (it == data.cend()) return false;

        if (std::distance(it, data.cend()) < repeatingGroupDimensions.blockLength * repeatingGroupDimensions.numInGroup) {
            std::cout << "Data is too short to contain all group blocks.\n";
            return false;
        }

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
                return false;
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
        return true;
    }

    static bool decodeIncremental(std::vector<uint8_t>::const_iterator &it, const std::vector<uint8_t> &data) {
        // If decoding fails at any point, return false.
        // Otherwise, return true.

        IncrementalPacketHeader incrementalPacketHeader;
        incrementalPacketHeader = decodeIncrementalPacketHeader(it, data);
        if (it == data.cend()) return false;

        while (it != data.cend()) {
            SBEHeader sbeHeader;
            sbeHeader = decodeSBEHeader(it, data);
            if (it == data.cend()) return false;

            if (std::distance(it, data.cend()) < sbeHeader.BlockLength) {
                std::cout << "Data is too short to contain a valid root block.\n";
                return false;
            }

            // Assume RootBlock's decode method fills the data and updates the iterator
            RootBlock rootBlock;
            rootBlock.data.insert(rootBlock.data.end(), it, it + sbeHeader.BlockLength);
            it += sbeHeader.BlockLength;
        }

        return true;
    }

    static SBEHeader decodeSBEHeader(std::vector<uint8_t>::const_iterator &it, const std::vector<uint8_t> &data) {
        if (std::distance(it, data.cend()) < sizeof(SBEHeader)) {
            std::cout << "Data is too short to contain a valid SBEHeader.\n";
            it = data.cend(); // Move iterator to the end to indicate failure
            return SBEHeader(); // Return default SBEHeader
        }

        SBEHeader sbeHeader;
        sbeHeader.BlockLength = fromBinary<uint16_t>(it); it += 2;
        std::cout << "BlockLength: " << sbeHeader.BlockLength << "\n";

        sbeHeader.TemplateID = fromBinary<uint16_t>(it); it += 2;
        std::cout << "TemplateID: " << sbeHeader.TemplateID << "\n";

        sbeHeader.SchemaID = fromBinary<uint16_t>(it); it += 2;
        std::cout << "SchemaID: " << sbeHeader.SchemaID << "\n";

        sbeHeader.Version = fromBinary<uint16_t>(it); it += 2;
        std::cout << "Version: " << sbeHeader.Version << "\n";

        return sbeHeader;
    }

    static IncrementalPacketHeader decodeIncrementalPacketHeader(std::vector<uint8_t>::const_iterator &it, const std::vector<uint8_t> &data) {
        if (std::distance(it, data.cend()) < sizeof(IncrementalPacketHeader)) {
            std::cout << "Data is too short to contain a valid IncrementalPacketHeader.\n";
            it = data.cend(); // Move iterator to the end to indicate failure
            return IncrementalPacketHeader(); // Return default IncrementalPacketHeader
        }

        IncrementalPacketHeader incrementalPacketHeader;
        incrementalPacketHeader.TransactTime = fromBinary<uint64_t>(it); it += 8;
        std::cout << "TransactTime: " << incrementalPacketHeader.TransactTime << "\n";

        incrementalPacketHeader.TradingSessionID = fromBinary<uint32_t>(it); it += 4;
        std::cout << "TradingSessionID: " << incrementalPacketHeader.TradingSessionID << "\n";

        return incrementalPacketHeader;
    }

    static MarketDataPacketHeader decodeMarketDataPacketHeader(std::vector<uint8_t>::const_iterator &it, const std::vector<uint8_t> &data) {
        if (std::distance(it, data.cend()) < sizeof(MarketDataPacketHeader)) {
            std::cout << "Data is too short to contain a valid MarketDataPacketHeader.\n";
            it = data.cend(); // Move iterator to the end to indicate failure
            return MarketDataPacketHeader(); // Return default MarketDataPacketHeader
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

        return marketDataPacketHeader;
    }

    static RepeatingGroupDimensions decodeRepeatingGroupDimensions(std::vector<uint8_t>::const_iterator &it, const std::vector<uint8_t> &data) {
        if (std::distance(it, data.cend()) < sizeof(RepeatingGroupDimensions)) {
            std::cout << "Data is too short to contain valid RepeatingGroupDimensions.\n";
            it = data.cend(); // Move iterator to the end to indicate failure
            return RepeatingGroupDimensions(); // Return default RepeatingGroupDimensions
        }

        RepeatingGroupDimensions repeatingGroupDimensions;
        repeatingGroupDimensions.blockLength = fromBinary<uint16_t>(it); it += 2;
        std::cout << "Repeating group block length: " << repeatingGroupDimensions.blockLength << "\n";

        repeatingGroupDimensions.numInGroup = fromBinary<uint8_t>(it); it += 1;
        std::cout << "Number in group: " << (int)repeatingGroupDimensions.numInGroup << "\n";

        return repeatingGroupDimensions;
    }



    template <typename T>
    static T fromBinary(const std::vector<uint8_t>::const_iterator &begin) {
        T value = 0;
        for (int i = 0; i < sizeof(T); i++) {
            value |= (T)(*(begin + i)) << (8 * i);
        }
        return value;
    }
};
