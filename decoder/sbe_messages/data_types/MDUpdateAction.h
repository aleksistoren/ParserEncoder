//
// Created by Aleksis Toren on 05.07.2023.
//

#pragma once
#include <cstdint>
#include <unordered_map>

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

std::ostream& operator<<(std::ostream& os, const MDUpdateAction& action) {
    static const std::unordered_map<MDUpdateAction, const char*> actionStrings = {
            { MDUpdateAction::New, "New" },
            { MDUpdateAction::Change, "Change" },
            { MDUpdateAction::Delete, "Delete" }
    };

    auto iter = actionStrings.find(action);
    if (iter != actionStrings.end()) {
        os << iter->second;
    } else {
        os << "Unknown";
    }

    return os;
}