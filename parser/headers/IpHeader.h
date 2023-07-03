//
// Created by Aleksis Toren on 03.07.2023.
//

#ifndef PARSERENCODER_IPHEADER_H
#define PARSERENCODER_IPHEADER_H

#endif //PARSERENCODER_IPHEADER_H

// IPv4 header (20 bytes without options)
struct IpHeader {
    uint8_t versionAndIhl;  // Version (4 bits) + Internet Header Length (4 bits)
    uint8_t typeOfService;  // Type of Service for QoS handling (1 byte)
    uint16_t totalLength;   // Total length of the IP packet, including headers and data (2 bytes)
    uint16_t identification; // Used for uniquely identifying the group of fragments of a single IP datagram (2 bytes)
    uint16_t flagsAndFragmentOffset; // 3 bits of flags and 13 bits of fragment offset
    uint8_t ttl;            // Time to Live (1 byte)
    uint8_t protocol;       // Protocol used in the data portion of the IP datagram (1 byte)
    uint16_t checksum;      // Header checksum (2 bytes)
    uint32_t srcAddr;       // Source IP address (4 bytes)
    uint32_t destAddr;      // Destination IP address (4 bytes)
};