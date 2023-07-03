cmake_minimum_required(VERSION 3.19)
project(ParserEncoder)

set(CMAKE_CXX_STANDARD 20)

add_executable(ParserEncoder main.cpp parser/parser.h parser/headers/PcapGlobalHeader.h parser/headers/PcapPacketHeader.h parser/headers/EthernetHeader.h parser/headers/IpHeader.h parser/headers/UdpHeader.h)