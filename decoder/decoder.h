//
// Created by Aleksis Toren on 04.07.2023.
//
#include "parts/SBEHeader.h"
#include "parts/RootBlock.h"
#include "parts/IncrementalPacketHeader.h"
#include "parts/RepeatingGroupDimensions.h"
#include "parts/MarketDataPacketHeader.h"
#include "SnapshotPacket.h"
#include "IncrementalPacket.h"

#ifndef PARSERENCODER_DECODER_H
#define PARSERENCODER_DECODER_H

#endif //PARSERENCODER_DECODER_H

class Decoder{
public:
    static bool tryDecodeSnapshot(const std::vector<uint8_t> &data, SnapshotPacket & snapshotPacket) {
        auto it = data.cbegin();
        auto end = data.cend();

        if (!tryDecodeToStruct(it, end, snapshotPacket.marketDataPacketHeader)) {
            //std::cout << "Data is too short to decode MarketDataPacketHeader.\n";
            return false;
        }

        if (!tryDecodeToStruct(it, end, snapshotPacket.sbeHeader)) {
            //std::cout << "Data is too short to decode SBEHeader.\n";
            return false;
        }

        if (std::distance(it, data.cend()) < snapshotPacket.sbeHeader.BlockLength) {
            //std::cout << "Data is too short to decode RootBlock.\n";
            return false;
        }

        snapshotPacket.rootBlock.data.insert(snapshotPacket.rootBlock.data.end(), it, it + snapshotPacket.sbeHeader.BlockLength);
        it += snapshotPacket.sbeHeader.BlockLength;

        if (!tryDecodeToStruct(it, end, snapshotPacket.repeatingGroupDimensions)) {
            //std::cout << "Data is too short to decode RepeatingGroupDimensions.\n";
            return false;
        }

        if (std::distance(it, data.cend()) != snapshotPacket.repeatingGroupDimensions.blockLength * snapshotPacket.repeatingGroupDimensions.numInGroup){
            return false;
        }

        for (int i = 0; i < snapshotPacket.repeatingGroupDimensions.numInGroup; i++){
            //std::vector<uint8_t> repeatingSection;
            snapshotPacket.repeatingSections.emplace_back();
            snapshotPacket.repeatingSections.back().data.insert(snapshotPacket.repeatingSections.back().data.end(),
                                                                it, it + snapshotPacket.repeatingGroupDimensions.blockLength);
            it += snapshotPacket.repeatingGroupDimensions.blockLength;
        }

        //std::cout<<"Snapshot \n"<<(int)sbeHeader.BlockLength<<" "<<(int)sbeHeader.TemplateID<<" "
        //         <<(int)repeatingGroupDimensions.numInGroup<<" "<<(int)repeatingGroupDimensions.blockLength<<"\n";


        return true;
    }

    static bool tryDecodeIncremental(const std::vector<uint8_t> &data, IncrementalPacket& incrementalPacket) {
        auto it = data.cbegin();
        auto end = data.cend();

        if (!tryDecodeToStruct(it, end, incrementalPacket.marketDataPacketHeader)) {
            //std::cout << "Data is too short to decode MarketDataPacketHeader.\n";
            return false;
        }

        if (!tryDecodeToStruct(it, end, incrementalPacket.incrementalPacketHeader)) {
            //std::cout << "Data is too short to decode IncrementalPacketHeader.\n";
            return false;
        }

        std::vector<std::pair<int,int>> res;
        // Loop for handling repeated SBEHeader-RootBlock pairs
        while (it != end) {
            SBEHeader sbeHeader{};
            if (!tryDecodeToStruct(it, end, sbeHeader)) {
                //std::cout << "Data is too short to decode SBEHeader.\n";
                return false;
            }

            if (std::distance(it, data.cend()) < sbeHeader.BlockLength) {
                //std::cout << "Data is too short to decode RootBlock.\n";
                return false;
            }

            RootBlock rootBlock;
            rootBlock.data.insert(rootBlock.data.end(), it, it + sbeHeader.BlockLength);
            it += sbeHeader.BlockLength;

            incrementalPacket.SbeMessages.emplace_back(sbeHeader, rootBlock);
        }

        //std::cout<<"Incremental type\n";

        for (auto i: res){
            //std::cout<<(int)i.first<<" "<<(int)i.second<<"\n";
        }

        return true;
    }
private:
    // A utility function to try to decode binary data directly into structures
    template<typename T>
    static bool tryDecodeToStruct(std::vector<uint8_t>::const_iterator& it, const std::vector<uint8_t>::const_iterator& end, T& result) {
        static_assert(std::is_pod<T>::value, "T must be a POD (Plain Old Data) type");
        auto d = std::distance(it, end);
        auto t = sizeof(T);
        if (std::distance(it, end) < sizeof(T)) {
            return false;
        }
        std::memcpy(&result, &(*it), sizeof(T));
        it += sizeof(T);
        return true;
    }
};