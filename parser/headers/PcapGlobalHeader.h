//
// Created by Aleksis Toren on 03.07.2023.
//

#ifndef PARSERENCODER_PCAPGLOBALHEADER_H
#define PARSERENCODER_PCAPGLOBALHEADER_H

#endif //PARSERENCODER_PCAPGLOBALHEADER_H

// pcap file global header (24 bytes)
struct PcapGlobalHeader {
    uint32_t magicNumber;   /* Magic number for file format recognition. If the value is '0xa1b2c3d4' then the file is in big endian format, if '0xd4c3b2a1' then the file is in little endian format. */
    uint16_t versionMajor;  /* Major version number of the pcap format being used; current version is 2. */
    uint16_t versionMinor;  /* Minor version number of the pcap format being used; current version is 4. */
    int32_t  thiszone;      /* Correction time in seconds between GMT (UTC) and the local timezone of the system in which the capture was taken. */
    uint32_t sigfigs;       /* Insignificant in most cases, intended to specify the precision of timestamps in the file. */
    uint32_t snaplen;       /* The maximum number of bytes captured for each packet, the remainder of the packet data is truncated. It's a snapshot length. */
    uint32_t network;       /* Data link type, defining the type of headers at the beginning of the packet. */
};

std::ostream& operator<<(std::ostream& os, const PcapGlobalHeader& header) {
    os << "Magic Number: " << std::hex << header.magicNumber << std::endl;
    os << "Version: " << header.versionMajor << "." << header.versionMinor << std::endl;
    os << "Timezone Correction: " << header.thiszone << " seconds" << std::endl;
    os << "Significant Figures: " << header.sigfigs << std::endl;
    os << "Snapshot Length: " << header.snaplen << " bytes" << std::endl;
    os << "Network Data Link Type: " << header.network;
    return os;
}