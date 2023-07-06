//
// Created by Aleksis Toren on 05.07.2023.
//

#pragma once
#include <cstdint>

#ifndef PARSERENCODER_MDFLAGSSET_H
#define PARSERENCODER_MDFLAGSSET_H

#endif //PARSERENCODER_MDFLAGSSET_H

#pragma pack(push, 1)
struct MDFlagsSet {
    uint64_t data;

    friend std::ostream& operator<<(std::ostream& os, const MDFlagsSet& flags) {
        os << flags.data;
        return os;
    }
};
#pragma pack(pop)