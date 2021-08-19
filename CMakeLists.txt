cmake_minimum_required(VERSION 3.13)
project(capstone)

add_executable(${PROJECT_NAME})
add_subdirectory(src)

set_property(TARGET capstone PROPERTY CXX_STANDARD 17)

target_compile_options(capstone PRIVATE -Wall -Wextra)
