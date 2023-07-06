//
// Created by Aleksis Toren on 05.07.2023.
//

#include <cstdint>

#ifndef PARSERENCODER_INT64NULL_H
#define PARSERENCODER_INT64NULL_H

#endif //PARSERENCODER_INT64NULL_H

struct Int64NULL {
    static constexpr int64_t NullValue = INT64_MIN;
    int64_t value;

    friend std::ostream& operator<<(std::ostream& os, const Int64NULL& obj) {
        if (obj.value == NullValue) {
            os << "NULL";
        } else {
            os << obj.value;
        }
        return os;
    }
};