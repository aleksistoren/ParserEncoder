//
// Created by Aleksis Toren on 03.07.2023.
//

#ifndef PARSERENCODER_PCAPPACKETHEADER_H
#define PARSERENCODER_PCAPPACKETHEADER_H

#endif //PARSERENCODER_PCAPPACKETHEADER_H

// pcap packet header (16 bytes)
struct PcapPacketHeader {
    uint32_t tsSec;         /* The date and time when the packet was captured. This value represents the number of seconds since January 1, 1970 00:00:00 GMT. */
    uint32_t tsUsec;        /* The microseconds when the packet was captured, as an offset to tsSec. */
    uint32_t inclLen;       /* The number of bytes of packet data actually captured and saved in the pcap file. It should never become larger than snaplen specified in the global header. */
    uint32_t origLen;       /* The length of the packet as it appeared on the network when it was captured. If inclLen and origLen differ, the packet has been truncated in the file. */
};

std::ostream& operator<<(std::ostream& os, const PcapPacketHeader& header) {
    os << "Timestamp: " << header.tsSec << "." << header.tsUsec << std::endl;
    os << "Included Length: " << header.inclLen << " bytes" << std::endl;
    os << "Original Length: " << header.origLen << " bytes";
    return os;
}