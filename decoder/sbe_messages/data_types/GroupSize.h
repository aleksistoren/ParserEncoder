//
// Created by Aleksis Toren on 05.07.2023.
//

#pragma once
#include <cstdint>

#ifndef PARSERENCODER_GROUPSIZE_H
#define PARSERENCODER_GROUPSIZE_H

#endif //PARSERENCODER_GROUPSIZE_H

#pragma pack(push, 1)
struct GroupSize {
    uint16_t blockLength;
    uint8_t numInGroup;
};
#pragma pack(pop)