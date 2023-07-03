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