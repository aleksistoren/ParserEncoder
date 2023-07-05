//
// Created by Aleksis Toren on 04.07.2023.
//

#ifndef PARSERENCODER_PCAPPACKET_H
#define PARSERENCODER_PCAPPACKET_H

#endif //PARSERENCODER_PCAPPACKET_H

struct PcapPacket{
    PcapPacketHeader packetHeader;
    EthernetHeader ethernetHeader;
    IpHeader ipHeader;
    UdpHeader udpHeader;
    std::vector<uint8_t> packetData;
};

std::ostream& operator<<(std::ostream& os, const PcapPacket& packet) {
    os << "Packet Header: " << packet.packetHeader << std::endl;
    os << "Ethernet Header: " << packet.ethernetHeader << std::endl;
    os << "IP Header: " << packet.ipHeader << std::endl;
    os << "UDP Header: " << packet.udpHeader << std::endl;
    os << "Packet Data: ";
    for (const auto& byte : packet.packetData) {
        os << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte) << " ";
    }
    return os;
}