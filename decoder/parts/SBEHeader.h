//
// Created by Aleksis Toren on 04.07.2023.
//

#ifndef PARSERENCODER_SBEHEADER_H
#define PARSERENCODER_SBEHEADER_H

#endif //PARSERENCODER_SBEHEADER_H

struct SBEHeader {
    uint16_t BlockLength;
    uint16_t TemplateID;
    uint16_t SchemaID;
    uint16_t Version;
};