set(CMAKE_CXX_STANDARD 17)
set(INCLUDE_PATH ${CMAKE_SOURCE_DIR}/include)

add_library(protocols_library "")

target_include_directories(
    protocols_library 
    PUBLIC
        ${INCLUDE_PATH})

target_sources(
    protocols_library 
    PRIVATE
        http_head.cpp
        not_found.cpp
        ${INCLUDE_PATH}/connection_tester/protocols/http_head.h
        ${INCLUDE_PATH}/connection_tester/protocols/not_found.h)

find_package(Threads REQUIRED)