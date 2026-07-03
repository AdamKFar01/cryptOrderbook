cmake_minimum_required(VERSION 3.15)
project(cryptOrderbook)
set(CMAKE_CXX_STANDARD 17)

find_package(nlohmann_json REQUIRED)
find_package(ixwebsocket REQUIRED)

add_executable(cryptOrderbook main.cpp
        include/OrderBook.h)

target_link_libraries(cryptOrderbook PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(cryptOrderbook PRIVATE ixwebsocket::ixwebsocket)

