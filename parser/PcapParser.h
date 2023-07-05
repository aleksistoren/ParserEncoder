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
    PcapParser(const std::string& path, const std::string &logPath = "logsPcapData.txt")
            : file(path, std::ios::binary), logFile(logPath) {
        if (!file) {
            throw std::runtime_error("Unable to open pcap file: " + path);
        }

        PcapGlobalHeader globalHeader{};
        file.read(reinterpret_cast<char *>(&globalHeader), sizeof(globalHeader));

        logFile << "Global Header:\n"
                << "Magic Number: " << std::hex << globalHeader.magicNumber << "\n"
                << "Version: " << globalHeader.versionMajor << "." << globalHeader.versionMinor << "\n"
                << "Time Zone Correction: " << globalHeader.thiszone << "\n"
                << "Timestamp Accuracy: " << globalHeader.sigfigs << "\n"
                << "Max Length of Packet Capture: " << globalHeader.snaplen << "\n"
                << "Network: " << globalHeader.network << "\n\n";
    }

    void parse() {
        //std::vector<PcapPacket> parsedResult;
        int index = 0;
        int cntBadPackets = 0;
        while (!file.eof()) {
            //if (i++ == 100000) return parsedResult;
            PcapPacket packet{};

            file.read(reinterpret_cast<char *>(&packet.packetHeader), sizeof(packet.packetHeader));

            if (packet.packetHeader.inclLen == 0 && file.eof()){
                break;
            }

            file.read(reinterpret_cast<char *>(&packet.ethernetHeader), sizeof(packet.ethernetHeader));

            file.read(reinterpret_cast<char *>(&packet.ipHeader), sizeof(packet.ipHeader));

            file.read(reinterpret_cast<char *>(&packet.udpHeader), sizeof(packet.udpHeader));

            // print packet header info...

            // print UDP header info...
            logFile << "UDP Header:\n"
                    << "Source Port: " << packet.udpHeader.srcPort << "\n"
                    << "Destination Port: " << packet.udpHeader.destPort << "\n"
                    << "Length: " << packet.udpHeader.length << "\n"
                    << "Checksum: " << packet.udpHeader.checksum << "\n";

            // Reading packet data
            packet.packetData.resize(
                    packet.packetHeader.inclLen - sizeof(EthernetHeader) - sizeof(IpHeader) - sizeof(UdpHeader));
            file.read(reinterpret_cast<char *>(packet.packetData.data()),
                      packet.packetHeader.inclLen - sizeof(EthernetHeader) - sizeof(IpHeader) - sizeof(UdpHeader));
            //parsedResult.push_back(packet);
            // Print the packet data
            logFile << "Packet data: ";
            for (char c : packet.packetData) {
                logFile << std::hex << std::setw(2) << std::setfill('0')
                        << static_cast<int>(static_cast<unsigned char>(c)) << ' ';
            }
            logFile << "\n" << "\n";

            IncrementalPacket incrementalPacket;
            if (!Decoder::tryDecodeIncremental(packet.packetData, incrementalPacket)){
                SnapshotPacket snapshotPacket;
                if (!Decoder::tryDecodeSnapshot(packet.packetData, snapshotPacket)){
                    ++cntBadPackets;
                    logFile<<"Incorrect message"<<std::endl;
                }else{
                    logFile<<snapshotPacket<<std::endl;
                }
            }else{
                logFile<<incrementalPacket<<std::endl;
            }

            index++;
        }

        logFile<<"cntBadPackets = "<<cntBadPackets<<"/"<<index<<"\n";
        std::cout<<"cntBadPackets = "<<cntBadPackets<<"/"<<index<<"\n";
    }
};