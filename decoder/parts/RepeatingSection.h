//
// Created by Aleksis Toren on 05.07.2023.
//

#pragma once
#include <vector>
#include <ios>
#include <iomanip>

#ifndef PARSERENCODER_REPEATINGSECTION_H
#define PARSERENCODER_REPEATINGSECTION_H

#endif //PARSERENCODER_REPEATINGSECTION_H

#pragma pack(push, 1)
struct RepeatingSection {
    std::vector<uint8_t> data;
};
#pragma pack(pop)

std::ostream& operator<<(std::ostream& os, const RepeatingSection& section) {
    os << "Data: ";
    for (const auto& value : section.data) {
        os << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(value) << " ";
    }
    return os;
}