//
// Created by Aleksis Toren on 05.07.2023.
//

#pragma once
#include <cstdint>

#ifndef PARSERENCODER_MDFLAGS2SET_H
#define PARSERENCODER_MDFLAGS2SET_H

#endif //PARSERENCODER_MDFLAGS2SET_H

#pragma pack(push, 1)
struct MDFlags2Set {
    uint64_t data;

    friend std::ostream& operator<<(std::ostream& os, const MDFlags2Set& flags) {
        os << flags.data;
        return os;
    }
};
#pragma pack(pop)