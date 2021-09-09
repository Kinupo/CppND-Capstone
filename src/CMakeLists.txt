set(CMAKE_CXX_STANDARD 17) 
# set(THREADS_PREFER_PTHREAD_FLAG ON)

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
            # ${Boost_INCLUDE_DIR})
            
target_sources(
    capstone 
        PRIVATE 
            main.cpp)

# find_package(Boost 1.71.0)
# find_package(Threads REQUIRED)

target_link_libraries(
    capstone 
        profile_lib
        user_interface_library
        configuration_lib
        connection_tester_library
        # ${Boost_LIBRARIES}
        # Threads::Threads
)