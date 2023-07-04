//
// Created by Aleksis Toren on 04.07.2023.
//

#ifndef PARSERENCODER_MARKETDATAPACKETHEADER_H
#define PARSERENCODER_MARKETDATAPACKETHEADER_H

#endif //PARSERENCODER_MARKETDATAPACKETHEADER_H

struct MarketDataPacketHeader {
    uint32_t MsgSeqNum;
    uint16_t MsgSize;
    uint16_t MsgFlags;
    uint64_t SendingTime;
};