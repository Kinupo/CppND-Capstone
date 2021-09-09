set(CMAKE_CXX_STANDARD 17)
set(INCLUDE_PATH ${CMAKE_SOURCE_DIR}/include)

add_subdirectory(protocols)

add_library(connection_tester_library "")

target_include_directories(
    connection_tester_library 
    PUBLIC
        ${INCLUDE_PATH})

target_sources(
    connection_tester_library 
    PRIVATE
        connection_tester.cpp
        connection.cpp
        protocol.cpp
        ${INCLUDE_PATH}/connection_tester/connection_tester.h
        ${INCLUDE_PATH}/connection_tester/connection.h
        ${INCLUDE_PATH}/connection_tester/connection_test_status.h
        ${INCLUDE_PATH}/connection_tester/protocol.h)

find_package(Threads REQUIRED)

target_link_libraries(
    connection_tester_library 
        protocols_library)