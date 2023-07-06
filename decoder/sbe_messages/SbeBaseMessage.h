//
// Created by Aleksis Toren on 06.07.2023.
//

#pragma once
#include <cstdint>

#ifndef PARSERENCODER_SBEBASEMESSAGE_H
#define PARSERENCODER_SBEBASEMESSAGE_H

#endif //PARSERENCODER_SBEBASEMESSAGE_H

#pragma pack(push, 1)
struct SbeBaseMessage{
    static const int32_t id;
    virtual void log(std::ostream &file) const =0;
};
#pragma pack(pop)