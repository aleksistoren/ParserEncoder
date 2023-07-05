//
// Created by Aleksis Toren on 05.07.2023.
//

#pragma once

#ifndef PARSERENCODER_MDENTRYTYPE_H
#define PARSERENCODER_MDENTRYTYPE_H

#endif //PARSERENCODER_MDENTRYTYPE_H

#pragma pack(push, 1)
enum class MDEntryType : char {
    Bid = '0',
    Offer = '1',
    EmptyBook = 'J'
};
#pragma pack(pop)