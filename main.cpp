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



int main() {
    // Open the pcap file
    std::ifstream file(PCAP_FILE_PATH, std::ios::binary);
    PcapParser parser = PcapParser(PCAP_FILE_PATH);

    parser.parse();

    /*int j=1;
    int cnt = 0;
    for (const auto& i:res){
        cout<<j++<<endl;
        if (!Decoder::tryDecodeIncremental(i.packetData)){
            if (!Decoder::tryDecodeSnapshot(i.packetData)){
                //cout<<"CAPEC"<<endl;
                ++cnt;
            }
        }
    }

    cout<<cnt<<endl;*/

    return 0;
}
