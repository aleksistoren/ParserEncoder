//
// Created by Aleksis Toren on 04.07.2023.
//

#pragma once

#ifndef PARSERENCODER_ROOTBLOCK_H
#define PARSERENCODER_ROOTBLOCK_H

#endif //PARSERENCODER_ROOTBLOCK_H

#pragma pack(push, 1)
struct RootBlock {
    std::vector<uint8_t> data;
};
#pragma pack(pop)

std::ostream& operator<<(std::ostream& os, const RootBlock& block) {
    os << "Data: ";
    for (const auto& value : block.data) {
        os << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(value) << " ";
    }
    return os;
}