//
// Created by Aleksis Toren on 04.07.2023.
//

#pragma once

#ifndef PARSERENCODER_REPEATINGGROUPDIMENSIONS_H
#define PARSERENCODER_REPEATINGGROUPDIMENSIONS_H

#endif //PARSERENCODER_REPEATINGGROUPDIMENSIONS_H

#pragma pack(push, 1)
struct RepeatingGroupDimensions {
    uint16_t blockLength;
    uint8_t numInGroup;
};
#pragma pack(pop)

std::ostream& operator<<(std::ostream& os, const RepeatingGroupDimensions& dimensions) {
    os << "Block Length: " << dimensions.blockLength << ", "
       << "Number in Group: " << static_cast<int>(dimensions.numInGroup);
    return os;
}