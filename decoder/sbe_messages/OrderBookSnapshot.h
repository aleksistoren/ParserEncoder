//
// Created by Aleksis Toren on 05.07.2023.
//

#pragma once
#include "data_types/MDFlagsSet.h"
#include "data_types/Int64NULL.h"
#include "data_types/Decimal5NULL.h"
#include "data_types/MDFlags2Set.h"
#include "data_types/MDEntryType.h"

#ifndef PARSERENCODER_ORDERBOOKSNAPSHOT_H
#define PARSERENCODER_ORDERBOOKSNAPSHOT_H

#endif //PARSERENCODER_ORDERBOOKSNAPSHOT_H

#pragma pack(push, 1)
struct OrderBookSnapshot {
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
};
#pragma pack(pop)