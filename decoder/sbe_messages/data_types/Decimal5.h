//
// Created by Aleksis Toren on 05.07.2023.
//

#pragma once
#include <cstdint>
#include <cmath>

#ifndef PARSERENCODER_DECIMAL5_H
#define PARSERENCODER_DECIMAL5_H

#endif //PARSERENCODER_DECIMAL5_H

#pragma pack(push, 1)
struct Decimal5 {
    int64_t mantissa;
    static const int8_t exponent = -5;

    double getDoubleValue() const {
        return mantissa * pow(10, exponent);
    }
};
#pragma pack(pop)