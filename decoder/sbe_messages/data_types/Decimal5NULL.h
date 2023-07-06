//
// Created by Aleksis Toren on 05.07.2023.
//

#include "Decimal5.h"

#ifndef PARSERENCODER_DECIMAL5NULL_H
#define PARSERENCODER_DECIMAL5NULL_H

#endif //PARSERENCODER_DECIMAL5NULL_H

struct Decimal5NULL : Decimal5 {
    static constexpr int64_t NullMantissa = INT64_MIN;

    friend std::ostream& operator<<(std::ostream& os, const Decimal5NULL& decimal) {
        if (decimal.mantissa == NullMantissa) {
            os << "NULL";
        } else {
            os << decimal.getDoubleValue();
        }
        return os;
    }
};