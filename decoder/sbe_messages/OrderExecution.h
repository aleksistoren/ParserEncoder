//
// Created by Aleksis Toren on 05.07.2023.
//

#pragma once
#include <cstdint>
#include "data_types/Decimal5.h"
#include "data_types/MDFlagsSet.h"
#include "data_types/MDFlags2Set.h"
#include "data_types/MDUpdateAction.h"
#include "data_types/MDEntryType.h"

#ifndef PARSERENCODER_ORDEREXECUTION_H
#define PARSERENCODER_ORDEREXECUTION_H

#endif //PARSERENCODER_ORDEREXECUTION_H

#pragma pack(push, 1)
struct OrderExecution {
    static const int32_t id = 16;
    int64_t MDEntryID;
    Decimal5 MDEntryPx;
    int64_t MDEntrySize;
    Decimal5 LastPx;
    int64_t LastQty;
    int64_t TradeID;
    MDFlagsSet MDFlags;
    MDFlags2Set MDFlags2;
    int32_t SecurityID;
    uint32_t RptSeq;
    MDUpdateAction MDUpdateAction;
    MDEntryType MDEntryType;
};
#pragma pack(pop)