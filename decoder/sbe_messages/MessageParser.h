//
// Created by Aleksis Toren on 06.07.2023.
//

#include <cstddef>
#include <vector>
#include "../parts/SBEHeader.h"
#include "SbeBaseMessage.h"
#include "OrderUpdate.h"
#include "OrderExecution.h"
#include "OrderBookSnapshot.h"

#ifndef PARSERENCODER_MESSAGEPARSER_H
#define PARSERENCODER_MESSAGEPARSER_H

#endif //PARSERENCODER_MESSAGEPARSER_H

class MessageParser {
    static const size_t SIZE_OF_BASE = 8;
public:
    static bool tryParse(SBEHeader sbeHeader, const std::vector<uint8_t>& data, SbeBaseMessage*& message, std::ofstream& file) {
        switch (sbeHeader.TemplateID) {
            case 15: {
                auto *orderUpdate = new OrderUpdate();
                if (!tryParseMessage(data, orderUpdate)){
                    return false;
                }
                message = orderUpdate;
                break;
            }
            case 16: {
                auto *orderExecution = new OrderExecution();
                if (!tryParseMessage(data, orderExecution)){
                    return false;
                }
                message = orderExecution;
                break;
            }
            case 17: {
                auto *orderBookSnapshot = new OrderBookSnapshot();
                if (!tryParseMessage(data, orderBookSnapshot)){
                    return false;
                }
                message = orderBookSnapshot;
                break;
            }
            default:
                return false;
        }
        return true;
    }

private:
    template<class T>
    static bool tryParseMessage(const std::vector<uint8_t>& data, T& message) {
        size_t size = sizeof(T) - SIZE_OF_BASE;
        if (data.size() >= size) {
            size_t headerSize = data.size() - size;
            const uint8_t* srcData = data.data() + headerSize;
            std::memcpy(message, srcData, size);
            return true;
        }
        return false;
    }
};
