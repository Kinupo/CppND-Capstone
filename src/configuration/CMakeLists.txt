set(CMAKE_CXX_STANDARD 17)
set(INCLUDE_PATH ${CMAKE_SOURCE_DIR}/include)

add_library(configuration_lib "")

target_include_directories(
    configuration_lib 
    PUBLIC
        ${INCLUDE_PATH})

target_sources(
    configuration_lib 
    PRIVATE
        ncurses_engine_config.cpp
        windows_configuration.cpp
        ${INCLUDE_PATH}/configuration/ncurses_engine_config.h
        ${INCLUDE_PATH}/configuration/windows_configuration.h
        ${INCLUDE_PATH}/configuration/connection_tester_configuration.h)