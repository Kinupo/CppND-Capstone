set(CMAKE_CXX_STANDARD 17)
set(INCLUDE_PATH ${CMAKE_SOURCE_DIR}/include)

add_library(windows_lib "")

target_include_directories(
    windows_lib 
    PUBLIC
        ${INCLUDE_PATH})

target_sources(
    windows_lib 
    PRIVATE
        notification_window.cpp
        menu_window.cpp
        table_window.cpp
        ${INCLUDE_PATH}/user_interface/windows/notification_window.h
        ${INCLUDE_PATH}/user_interface/windows/menu_window.h
        ${INCLUDE_PATH}/user_interface/windows/table_window.h
        ${INCLUDE_PATH}/user_interface/windows/row.h
        ${INCLUDE_PATH}/user_interface/windows/column.h
        )

find_library(CURSES_LIBRARIES curses)

target_link_libraries(
    windows_lib 
        ${CURSES_LIBRARIES})