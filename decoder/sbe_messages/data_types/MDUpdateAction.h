//
// Created by Aleksis Toren on 05.07.2023.
//

#pragma once
#include <cstdint>

#ifndef PARSERENCODER_MDUPDATEACTION_H
#define PARSERENCODER_MDUPDATEACTION_H

#endif //PARSERENCODER_MDUPDATEACTION_H

#pragma pack(push, 1)
enum class MDUpdateAction : uint8_t {
    New = 0,
    Change = 1,
    Delete = 2
};
#pragma pack(pop)