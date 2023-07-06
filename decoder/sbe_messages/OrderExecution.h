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
struct OrderExecution: SbeBaseMessage {
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

    friend std::ostream& operator<<(std::ostream& os, const OrderExecution& orderExecution) {
        os << "MDEntryID: " << orderExecution.MDEntryID << std::endl;
        os << "MDEntryPx: " << orderExecution.MDEntryPx << std::endl;
        os << "MDEntrySize: " << orderExecution.MDEntrySize << std::endl;
        os << "LastPx: " << orderExecution.LastPx << std::endl;
        os << "LastQty: " << orderExecution.LastQty << std::endl;
        os << "TradeID: " << orderExecution.TradeID << std::endl;
        os << "MDFlags: " << orderExecution.MDFlags << std::endl;
        os << "MDFlags2: " << orderExecution.MDFlags2 << std::endl;
        os << "SecurityID: " << orderExecution.SecurityID << std::endl;
        os << "RptSeq: " << orderExecution.RptSeq << std::endl;
        os << "MDUpdateAction: " << orderExecution.MDUpdateAction << std::endl;
        os << "MDEntryType: " << orderExecution.MDEntryType << std::endl;
        return os;
    }

    void log(std::ostream &file) const override{
        file<<"OrderExecution: "<<std::endl;
        file<<(*this);
    }
};
#pragma pack(pop)