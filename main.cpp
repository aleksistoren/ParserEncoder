//
// Created by Aleksis Toren on 03.07.2023.
//

#include <fstream>
#include <iostream>
#include <cstdint>
#include <vector>
#include <iomanip>
#include "parser/PcapParser.h"
//#include "decoder/decoder.h"

const std::string PCAP_FILE_PATH = "/Users/aleksistoren/Downloads/2023-04-25.1849-1906.pcap";

using namespace std;

void solve(){
    // Open the pcap file
    std::ifstream file(PCAP_FILE_PATH, std::ios::binary);
    PcapParser parser = PcapParser(PCAP_FILE_PATH);

    parser.parse();
}

int main() {
    // Start the timer
    auto start = std::chrono::high_resolution_clock::now();

    solve();

    // Stop the timer
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate the duration
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    // Print the execution time
    std::cout << "Execution time: " << duration.count() << " microseconds" << std::endl;

    return 0;
}
