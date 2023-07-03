//
// Created by Aleksis Toren on 03.07.2023.
//

#include "headers/PcapGlobalHeader.h"
#include "headers/PcapPacketHeader.h"
#include "headers/EthernetHeader.h"
#include "headers/IpHeader.h"
#include "headers/UdpHeader.h"

#ifndef PARSERENCODER_PARSER_H
#define PARSERENCODER_PARSER_H

#endif //PARSERENCODER_PARSER_H

class PcapParser {
    std::ifstream file;
    std::ofstream logFile;

public:
    PcapParser(const std::string& path, const std::string &logPath = "log.txt")
            : file(path, std::ios::binary), logFile(logPath)
    {
        if (!file) {
            throw std::runtime_error("Unable to open pcap file: " + path);
        }

        PcapGlobalHeader globalHeader{};
        file.read(reinterpret_cast<char*>(&globalHeader), sizeof(globalHeader));

        std::cout << "Global Header:\n"
                  << "Magic Number: " << std::hex << globalHeader.magicNumber << "\n"
                  << "Version: " << globalHeader.versionMajor << "." << globalHeader.versionMinor << "\n"
                  << "Time Zone Correction: " << globalHeader.thiszone << "\n"
                  << "Timestamp Accuracy: " << globalHeader.sigfigs << "\n"
                  << "Max Length of Packet Capture: " << globalHeader.snaplen << "\n"
                  << "Network: " << globalHeader.network << "\n\n";
    }

    void parse() {
        while (!file.eof()) {
            PcapPacketHeader packetHeader{};
            file.read(reinterpret_cast<char*>(&packetHeader), sizeof(packetHeader));

            if (!file) {
                break;
            }

            EthernetHeader ethernetHeader{};
            file.read(reinterpret_cast<char*>(&ethernetHeader), sizeof(ethernetHeader));

            IpHeader ipHeader{};
            file.read(reinterpret_cast<char*>(&ipHeader), sizeof(ipHeader));

            UdpHeader udpHeader{};
            file.read(reinterpret_cast<char*>(&udpHeader), sizeof(udpHeader));

            // print packet header info...

            // print UDP header info...
            std::cout << "UDP Header:\n"
                      << "Source Port: " << udpHeader.srcPort << "\n"
                      << "Destination Port: " << udpHeader.destPort << "\n"
                      << "Length: " << udpHeader.length << "\n"
                      << "Checksum: " << udpHeader.checksum << "\n";

            // Reading packet data
            std::vector<uint8_t> packetData(packetHeader.inclLen - sizeof(EthernetHeader) - sizeof(IpHeader) - sizeof(UdpHeader));
            file.read(reinterpret_cast<char*>(packetData.data()), packetHeader.inclLen - sizeof(EthernetHeader) - sizeof(IpHeader) - sizeof(UdpHeader));

            // Print the packet data
            logFile << "Packet data: ";
            for (char c : packetData) {
                logFile << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(static_cast<unsigned char>(c)) << ' ';
            }
            logFile << "\n";
        }
    }
};