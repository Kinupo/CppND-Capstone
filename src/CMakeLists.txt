set(CMAKE_CXX_STANDARD 17) 

set(INCLUDE_PATH ${CMAKE_SOURCE_DIR}/include)

add_subdirectory(user_interface)
add_subdirectory(configuration)
add_subdirectory(file_reader)
add_subdirectory(profile)
add_subdirectory(connection_tester)

target_include_directories(
    capstone 
        PUBLIC 
            ${INCLUDE_PATH})
            
target_sources(
    capstone 
        PRIVATE 
            main.cpp)

target_link_libraries(
    capstone 
        profile_lib
        user_interface_library
        configuration_lib
        connection_tester_library
)