set(CMAKE_CXX_STANDARD 17)
set(INCLUDE_PATH ${CMAKE_SOURCE_DIR}/include)

add_subdirectory(windows)

add_library(user_interface_library "")

target_include_directories(
    user_interface_library 
    PUBLIC
        ${INCLUDE_PATH})

target_sources(
    user_interface_library 
    PRIVATE
        window_repository.cpp
        ncurses_engine.cpp
        window.cpp
        ${INCLUDE_PATH}/user_interface/window_repository.h
        ${INCLUDE_PATH}/user_interface/ncurses_engine.h
        ${INCLUDE_PATH}/user_interface/window.h)

find_library(CURSES_LIBRARIES curses)
find_package(Threads REQUIRED)

target_link_libraries(
    user_interface_library 
        windows_lib
        ${CURSES_LIBRARIES})