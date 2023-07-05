//
// Created by Aleksis Toren on 04.07.2023.
//

#pragma once

#ifndef PARSERENCODER_MARKETDATAPACKETHEADER_H
#define PARSERENCODER_MARKETDATAPACKETHEADER_H

#endif //PARSERENCODER_MARKETDATAPACKETHEADER_H

#pragma pack(push, 1)
struct MarketDataPacketHeader {
    uint32_t MsgSeqNum;
    uint16_t MsgSize;
    uint16_t MsgFlags;
    uint64_t SendingTime;
};
#pragma pack(pop)

std::ostream& operator<<(std::ostream& os, const MarketDataPacketHeader& header) {
    os << "MsgSeqNum: " << header.MsgSeqNum << ", "
       << "MsgSize: " << header.MsgSize << ", "
       << "MsgFlags: " << header.MsgFlags << ", "
       << "SendingTime: " << header.SendingTime;
    return os;
}