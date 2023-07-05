//
// Created by Aleksis Toren on 04.07.2023.
//

#pragma once

#ifndef PARSERENCODER_INCREMENTALPACKETHEADER_H
#define PARSERENCODER_INCREMENTALPACKETHEADER_H

#endif //PARSERENCODER_INCREMENTALPACKETHEADER_H

#pragma pack(push, 1)
struct IncrementalPacketHeader {
    uint64_t TransactTime;
    uint32_t TradingSessionID;
};
#pragma pack(pop)

std::ostream& operator<<(std::ostream& os, const IncrementalPacketHeader& header) {
    os << "TransactTime: " << header.TransactTime << ", "
       << "TradingSessionID: " << header.TradingSessionID;
    return os;
}