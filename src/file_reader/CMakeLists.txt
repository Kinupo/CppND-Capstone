set(INCLUDE_PATH ${CMAKE_SOURCE_DIR}/include)

add_library(file_reader_lib "")

target_include_directories(
    file_reader_lib 
    PUBLIC
        ${INCLUDE_PATH})

target_sources(
    file_reader_lib 
    PRIVATE
        file_reader.cpp
        ${INCLUDE_PATH}/file_reader/file_reader.h)