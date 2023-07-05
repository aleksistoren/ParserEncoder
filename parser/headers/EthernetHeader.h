//
// Created by Aleksis Toren on 03.07.2023.
//

#ifndef PARSERENCODER_ETHERNETHEADER_H
#define PARSERENCODER_ETHERNETHEADER_H

#endif //PARSERENCODER_ETHERNETHEADER_H

// Ethernet II header (14 bytes)
struct EthernetHeader {
    uint8_t destMac[6];     // Destination MAC address (6 bytes)
    uint8_t srcMac[6];      // Source MAC address (6 bytes)
    uint16_t type;          // EtherType field (2 bytes) to indicate which protocol is encapsulated in the payload of the frame
};

std::ostream& operator<<(std::ostream& os, const EthernetHeader& header) {
    os << "Destination MAC: ";
    for (int i = 0; i < 6; ++i) {
        os << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(header.destMac[i]);
        if (i != 5)
            os << ":";
    }
    os << std::endl;

    os << "Source MAC: ";
    for (int i = 0; i < 6; ++i) {
        os << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(header.srcMac[i]);
        if (i != 5)
            os << ":";
    }
    os << std::endl;

    os << "EtherType: " << std::hex << header.type;
    return os;
}