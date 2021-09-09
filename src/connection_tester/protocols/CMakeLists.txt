set(CMAKE_CXX_STANDARD 17)
set(INCLUDE_PATH ${CMAKE_SOURCE_DIR}/include)
set(THREADS_PREFER_PTHREAD_FLAG ON)

add_library(protocols_library "")

target_include_directories(
    protocols_library 
    PUBLIC
        ${INCLUDE_PATH}
        ${Boost_INCLUDE_DIR})

target_sources(
    protocols_library 
    PRIVATE
        http_head.cpp
        not_found.cpp
        ${INCLUDE_PATH}/connection_tester/protocols/http_head.h
        ${INCLUDE_PATH}/connection_tester/protocols/not_found.h)

find_package(Boost 1.71.0)
find_package(Threads REQUIRED)

target_link_libraries(
    protocols_library 
        ${Boost_LIBRARIES}
        Threads::Threads
)

