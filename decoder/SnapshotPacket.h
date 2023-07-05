//
// Created by Aleksis Toren on 05.07.2023.
//

#include <vector>
#include "parts/MarketDataPacketHeader.h"
#include "parts/SBEHeader.h"
#include "parts/RootBlock.h"
#include "parts/RepeatingGroupDimensions.h"
#include "parts/RepeatingSection.h"

#ifndef PARSERENCODER_SNAPSHOTPACKET_H
#define PARSERENCODER_SNAPSHOTPACKET_H

#endif //PARSERENCODER_SNAPSHOTPACKET_H

struct SnapshotPacket{
    MarketDataPacketHeader marketDataPacketHeader;
    SBEHeader sbeHeader;
    RootBlock rootBlock;
    RepeatingGroupDimensions repeatingGroupDimensions;
    std::vector<RepeatingSection> repeatingSections;
};