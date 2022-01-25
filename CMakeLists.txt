cmake_minimum_required(VERSION 3.21)
project(SuffixFS C)

set(CMAKE_C_STANDARD 99)

include(Suffix/CMakeLists.txt)

include_directories(Suffix)

SUFFIX_GET_SOURCES(SUFFIX_SOURCES)

add_executable(Suffix main.c ${SUFFIX_SOURCES})

target_link_libraries(Suffix Ws2_32 Mswsock AdvApi32)