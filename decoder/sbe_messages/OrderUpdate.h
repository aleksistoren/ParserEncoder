//
// Created by Aleksis Toren on 05.07.2023.
//

#pragma once
#include <cstdint>
#include <iomanip>
#include <iostream>
#include "data_types/Decimal5.h"
#include "data_types/MDFlagsSet.h"
#include "data_types/MDFlags2Set.h"
#include "data_types/MDUpdateAction.h"
#include "data_types/MDEntryType.h"
#include "SbeBaseMessage.h"

#ifndef PARSERENCODER_ORDERUPDATE_H
#define PARSERENCODER_ORDERUPDATE_H

#endif //PARSERENCODER_ORDERUPDATE_H

#pragma pack(push, 1)
struct OrderUpdate: SbeBaseMessage {
    static const int32_t id = 15;
    int64_t MDEntryID;
    Decimal5 MDEntryPx;
    int64_t MDEntrySize;
    MDFlagsSet MDFlags;
    MDFlags2Set MDFlags2;
    int32_t SecurityID;
    uint32_t RptSeq;
    MDUpdateAction MDUpdateAction;
    MDEntryType MDEntryType;

    friend std::ostream& operator<<(std::ostream& os, const OrderUpdate& orderUpdate) {
        os << "MDEntryID: " << orderUpdate.MDEntryID << std::endl;
        os << "MDEntryPx: " << orderUpdate.MDEntryPx << std::endl;
        os << "MDEntrySize: " << orderUpdate.MDEntrySize << std::endl;
        os << "MDFlags: " << orderUpdate.MDFlags << std::endl;
        os << "MDFlags2: " << orderUpdate.MDFlags2 << std::endl;
        os << "SecurityID: " << orderUpdate.SecurityID << std::endl;
        os << "RptSeq: " << orderUpdate.RptSeq << std::endl;
        os << "MDUpdateAction: " << orderUpdate.MDUpdateAction << std::endl;
        os << "MDEntryType: " << orderUpdate.MDEntryType << std::endl;
        return os;
    }
};
#pragma pack(pop)