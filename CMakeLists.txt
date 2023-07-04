cmake_minimum_required(VERSION 3.19)
project(ParserEncoder)

set(CMAKE_CXX_STANDARD 20)

add_executable(ParserEncoder main.cpp parser/PcapParser.h parser/headers/PcapGlobalHeader.h parser/headers/PcapPacketHeader.h parser/headers/EthernetHeader.h parser/headers/IpHeader.h parser/headers/UdpHeader.h decoder/decoder.h decoder/parts/MarketDataPacketHeader.h decoder/parts/SBEHeader.h decoder/parts/RootBlock.h decoder/parts/RepeatingGroupDimensions.h decoder/parts/GroupBlock.h decoder/parts/IncrementalPacketHeader.h parser/PcapPacket.h)