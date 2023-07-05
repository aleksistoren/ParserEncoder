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

std::ostream& operator<<(std::ostream& os, const SnapshotPacket& packet) {
    os << "Market Data Packet Header: " << packet.marketDataPacketHeader << std::endl;
    os << "SBE Header: " << packet.sbeHeader << std::endl;
    os << "Root Block: " << packet.rootBlock << std::endl;
    os << "Repeating Group Dimensions: " << packet.repeatingGroupDimensions << std::endl;
    os << "Repeating Sections: " << std::endl;
    for (const auto& section : packet.repeatingSections) {
        os << section << std::endl;
    }
    return os;
}