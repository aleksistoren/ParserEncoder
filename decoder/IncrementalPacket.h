//
// Created by Aleksis Toren on 05.07.2023.
//

#include <vector>
#include "parts/MarketDataPacketHeader.h"
#include "parts/IncrementalPacketHeader.h"
#include "parts/SBEHeader.h"
#include "parts/RootBlock.h"

#ifndef PARSERENCODER_INCREMENTALPACKET_H
#define PARSERENCODER_INCREMENTALPACKET_H

#endif //PARSERENCODER_INCREMENTALPACKET_H

struct IncrementalPacket{
    MarketDataPacketHeader marketDataPacketHeader;
    IncrementalPacketHeader incrementalPacketHeader;
    std::vector<std::pair<SBEHeader, RootBlock> > SbeMessages;
};