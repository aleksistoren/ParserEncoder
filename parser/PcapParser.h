//
// Created by Aleksis Toren on 03.07.2023.
//

#include "headers/PcapGlobalHeader.h"
#include "headers/PcapPacketHeader.h"
#include "headers/EthernetHeader.h"
#include "headers/IpHeader.h"
#include "headers/UdpHeader.h"
#include "PcapPacket.h"
#include "../decoder/decoder.h"

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
            //if (i++ == 100000) return parsedResult;
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
            if (!Decoder::tryDecodeIncremental(packet.packetData, incrementalPacket)) {
                SnapshotPacket snapshotPacket;
                if (!Decoder::tryDecodeSnapshot(packet.packetData, snapshotPacket)) {
                    ++cntBadPackets;
                    logFile << "Incorrect message"
                            << std::endl
                            << std::endl;
                } else {
                    logFile << snapshotPacket
                            << std::endl
                            << std::endl;
                }
            } else {
                logFile << incrementalPacket
                        << std::endl
                        << std::endl;
            }

            index++;
        }

        logFile << "cntBadPackets = " << cntBadPackets << "/" << index
                << std::endl;
        std::cout << "cntBadPackets = " << cntBadPackets << "/" << index
                  << std::endl;
    }
};