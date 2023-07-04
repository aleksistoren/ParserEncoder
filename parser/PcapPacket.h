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