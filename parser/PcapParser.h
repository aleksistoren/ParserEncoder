//
// Created by Aleksis Toren on 03.07.2023.
//

#include "headers/PcapGlobalHeader.h"
#include "headers/PcapPacketHeader.h"
#include "headers/EthernetHeader.h"
#include "headers/IpHeader.h"
#include "headers/UdpHeader.h"
#include "PcapPacket.h"
#include "../decoder/Decoder.h"
#include "../decoder/sbe_messages/SbeBaseMessage.h"
#include "../decoder/sbe_messages/MessageParser.h"

#ifndef PARSERENCODER_PARSER_H
#define PARSERENCODER_PARSER_H

#endif //PARSERENCODER_PARSER_H

class PcapParser {
    std::ifstream file;
    std::ofstream logFile;
    int countOfIncorrectMessages = 0;
    int countOfMessages = 0;

public:
    PcapParser(const std::string &path, const std::string &logPath = "logsPcapData.txt")
            : file(path, std::ios::binary), logFile(logPath) {
        if (!file) {
            throw std::runtime_error("Unable to open pcap file: " + path);
        }

        PcapGlobalHeader globalHeader{};
        file.read(reinterpret_cast<char *>(&globalHeader), sizeof(globalHeader));

        logFile << "Global Header:\n"
                << globalHeader
                << std::endl
                << std::endl;

    }

    void parse() {
        //std::vector<PcapPacket> parsedResult;
        int index = 0;
        int cntBadPackets = 0;
        while (!file.eof()) {
            std::cout<<index++<<std::endl;
            //if (index == 100000) break;
            PcapPacket packet{};

            file.read(reinterpret_cast<char *>(&packet.packetHeader), sizeof(packet.packetHeader));

            if (packet.packetHeader.inclLen == 0 && file.eof()) {
                break;
            }

            file.read(reinterpret_cast<char *>(&packet.ethernetHeader), sizeof(packet.ethernetHeader));

            file.read(reinterpret_cast<char *>(&packet.ipHeader), sizeof(packet.ipHeader));

            file.read(reinterpret_cast<char *>(&packet.udpHeader), sizeof(packet.udpHeader));

            // Reading packet data
            packet.packetData.resize(
                    packet.packetHeader.inclLen - sizeof(EthernetHeader) - sizeof(IpHeader) - sizeof(UdpHeader));
            file.read(reinterpret_cast<char *>(packet.packetData.data()),
                      packet.packetHeader.inclLen - sizeof(EthernetHeader) - sizeof(IpHeader) - sizeof(UdpHeader));

            logFile << "Packet: \n"
                    << packet
                    << std::endl;

            IncrementalPacket incrementalPacket;
            if (Decoder::tryDecodeIncremental(packet.packetData, incrementalPacket)) {
                logFile << incrementalPacket
                        << std::endl
                        << std::endl;
                logFile << "Decoded messages: " << std::endl;
                for (const auto& i: incrementalPacket.SbeMessages){
                    logFile<<"Sbe Header: "<<std::endl;
                    logFile<<i.first<<std::endl;
                    SbeBaseMessage *message = nullptr;
                    decodeMesage(i.first, i.second.data, message);
                    delete message;
                    logFile<<std::endl;
                }
                continue;
            }
            SnapshotPacket snapshotPacket;
            if (Decoder::tryDecodeSnapshot(packet.packetData, snapshotPacket)) {
                logFile << snapshotPacket
                        << std::endl
                        << std::endl;
                logFile<<"Sbe Header: "
                       <<snapshotPacket.sbeHeader<<std::endl;
                for (auto repeatingSection: snapshotPacket.repeatingSections){
                    SbeBaseMessage *message = nullptr;
                    decodeMesage(snapshotPacket.sbeHeader, repeatingSection.data, message);
                    delete message;
                }
                continue;
            }

            ++cntBadPackets;
            logFile << "Incorrect message"
                    << std::endl
                    << std::endl;
        }

        logFile << "cntBadPackets = " << cntBadPackets << "/" << index
                << std::endl;
        std::cout << "cntBadPackets = " << cntBadPackets << "/" << index
                  << std::endl;

        logFile << "countOfIncorrectMessages = " << countOfIncorrectMessages << "/" << countOfMessages
                << std::endl;
        std::cout << "countOfIncorrectMessages = " << countOfIncorrectMessages << "/" << countOfMessages
                  << std::endl;


    }
private:
    void decodeMesage(SBEHeader sbeHeader, const std::vector<uint8_t>& data, SbeBaseMessage *message){
        countOfMessages++;
        if (MessageParser::tryParse(sbeHeader, data, message)){
            if (sbeHeader.TemplateID == OrderUpdate::id) {
                logFile << "OrderUpdate" <<std::endl;
                logFile << (*(OrderUpdate*)(message)) << std::endl;
                return;
            }
            if (sbeHeader.TemplateID == OrderExecution::id) {
                logFile << "OrderExecution" <<std::endl;
                logFile << (*(OrderExecution*)(message)) << std::endl;
                return;
            }
            if (sbeHeader.TemplateID == OrderBookSnapshot::id) {
                logFile << "OrderBookSnapshot" <<std::endl;
                logFile << (*(OrderBookSnapshot*)(message)) << std::endl;
                return;
            }

        }else{
            logFile<<"Incorrect message"<<std::endl;
            countOfIncorrectMessages++;
        }
    }
};
