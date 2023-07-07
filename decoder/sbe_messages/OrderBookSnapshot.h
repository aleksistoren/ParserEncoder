//
// Created by Aleksis Toren on 05.07.2023.
//

#pragma once
#include "data_types/MDFlagsSet.h"
#include "data_types/Int64NULL.h"
#include "data_types/Decimal5NULL.h"
#include "data_types/MDFlags2Set.h"
#include "data_types/MDEntryType.h"
#include "SbeBaseMessage.h"

#ifndef PARSERENCODER_ORDERBOOKSNAPSHOT_H
#define PARSERENCODER_ORDERBOOKSNAPSHOT_H

#endif //PARSERENCODER_ORDERBOOKSNAPSHOT_H

#pragma pack(push, 1)
struct OrderBookSnapshot: SbeBaseMessage {
    static const int32_t id = 17;
    int32_t SecurityID;
    uint32_t LastMsgSeqNumProcessed;
    uint32_t RptSeq;
    uint32_t ExchangeTradingSessionID;
    uint32_t NoMDEntries;
    Int64NULL MDEntryID;
    uint64_t TransactTime;
    Decimal5NULL MDEntryPx;
    Int64NULL MDEntrySize;
    Int64NULL TradeID;
    MDFlagsSet MDFlags;
    MDFlags2Set MDFlags2;
    MDEntryType MDEntryType;

    friend std::ostream& operator<<(std::ostream& os, const OrderBookSnapshot& orderBookSnapshot) {
        os << "SecurityID: " << orderBookSnapshot.SecurityID << std::endl;
        os << "LastMsgSeqNumProcessed: " << orderBookSnapshot.LastMsgSeqNumProcessed << std::endl;
        os << "RptSeq: " << orderBookSnapshot.RptSeq << std::endl;
        os << "ExchangeTradingSessionID: " << orderBookSnapshot.ExchangeTradingSessionID << std::endl;
        os << "NoMDEntries: " << orderBookSnapshot.NoMDEntries << std::endl;
        os << "MDEntryID: " << orderBookSnapshot.MDEntryID << std::endl;
        os << "TransactTime: " << orderBookSnapshot.TransactTime << std::endl;
        os << "MDEntryPx: " << orderBookSnapshot.MDEntryPx << std::endl;
        os << "MDEntrySize: " << orderBookSnapshot.MDEntrySize << std::endl;
        os << "TradeID: " << orderBookSnapshot.TradeID << std::endl;
        os << "MDFlags: " << orderBookSnapshot.MDFlags << std::endl;
        os << "MDFlags2: " << orderBookSnapshot.MDFlags2 << std::endl;
        os << "MDEntryType: " << orderBookSnapshot.MDEntryType << std::endl;
        return os;
    }
};
#pragma pack(pop)