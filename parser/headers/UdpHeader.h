//
// Created by Aleksis Toren on 03.07.2023.
//

#ifndef PARSERENCODER_UDPHEADER_H
#define PARSERENCODER_UDPHEADER_H

#endif //PARSERENCODER_UDPHEADER_H

// UDP header (8 bytes)
struct UdpHeader {
    uint16_t srcPort;       // Source port number (2 bytes)
    uint16_t destPort;      // Destination port number (2 bytes)
    uint16_t length;        // Length of the UDP header and UDP data (2 bytes)
    uint16_t checksum;      // Checksum for error checking (2 bytes)
};