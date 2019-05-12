cmake_minimum_required(VERSION 3.13)
project(TecelaSQL)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(client)
