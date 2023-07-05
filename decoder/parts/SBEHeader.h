//
// Created by Aleksis Toren on 04.07.2023.
//

#pragma once

#ifndef PARSERENCODER_SBEHEADER_H
#define PARSERENCODER_SBEHEADER_H

#endif //PARSERENCODER_SBEHEADER_H

#pragma pack(push, 1)
struct SBEHeader {
    uint16_t BlockLength;
    uint16_t TemplateID;
    uint16_t SchemaID;
    uint16_t Version;
};
#pragma pack(pop)

std::ostream& operator<<(std::ostream& os, const SBEHeader& header) {
    os << "Block Length: " << header.BlockLength << ", "
       << "Template ID: " << header.TemplateID << ", "
       << "Schema ID: " << header.SchemaID << ", "
       << "Version: " << header.Version;
    return os;
}