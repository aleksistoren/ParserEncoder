//
// Created by Aleksis Toren on 03.07.2023.
//

#include <fstream>
#include <iostream>
#include <cstdint>
#include <vector>
#include <iomanip>
#include "parser/parser.h"

const std::string PCAP_FILE_PATH = "/Users/aleksistoren/Downloads/2023-04-25.1849-1906.pcap";

// Message IDs
const uint8_t ORDER_UPDATE = 15;
const uint8_t ORDER_EXECUTION = 16;
const uint8_t ORDER_BOOK_SNAPSHOT = 17;

struct OrderUpdate {
    uint8_t msgid = ORDER_UPDATE;
    int64_t MDEntryID;
    double MDEntryPx;
    int64_t MDEntrySize;
    uint8_t MDFlags;
    uint8_t MDFlags2;
    int32_t SecurityID;
    uint32_t RptSeq;
    uint32_t MDUpdateAction;
    uint32_t MDEntryType;
};

int main() {
    // Open the pcap file
    std::ifstream file(PCAP_FILE_PATH, std::ios::binary);
    PcapParser parser = PcapParser(PCAP_FILE_PATH);

    parser.parse();

    return 0;
}
