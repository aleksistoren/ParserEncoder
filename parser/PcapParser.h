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
            index++;
            if (index == 10000) return;
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
                    SbeBaseMessage *message = nullptr;
                    logFile<<"Sbe Header: "<<std::endl;
                    logFile<<i.first<<std::endl;
                    if (MessageParser::tryParse(i.first, i.second.data, message, logFile)){
                        message->log(logFile);
                    }else{
                        logFile<<"Incorrect message"<<std::endl;
                    }
                    logFile<<std::endl;
                }
                continue;
            }
            SnapshotPacket snapshotPacket;
            if (!Decoder::tryDecodeSnapshot(packet.packetData, snapshotPacket)) {
                ++cntBadPackets;
                logFile << "Incorrect message"
                        << std::endl
                        << std::endl;
                continue;
            }

            logFile << snapshotPacket
                    << std::endl
                    << std::endl;

            std::cout<<index<<std::endl;
        }

        logFile << "cntBadPackets = " << cntBadPackets << "/" << index
                << std::endl;
        std::cout << "cntBadPackets = " << cntBadPackets << "/" << index
                  << std::endl;
    }
private:
    template<class T>
    void logMessage(T* message){
        logFile<<(*message)<<std::endl;
    }
};