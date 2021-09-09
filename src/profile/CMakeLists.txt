set(INCLUDE_PATH ${CMAKE_SOURCE_DIR}/include)

add_library(profile_lib "")

target_include_directories(
    profile_lib 
    PUBLIC
        ${INCLUDE_PATH})

target_sources(
    profile_lib 
    PRIVATE
        profile.cpp
        profile_loader.cpp
        ${INCLUDE_PATH}/profile/profile_loader.h
        ${INCLUDE_PATH}/profile/profile.h)

target_link_libraries(
    profile_lib
        file_reader_lib)