cmake_minimum_required(VERSION 3.13)
project(TecelaSQL)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
add_executable(TeceleSQL main.cpp)

add_subdirectory(src)
add_subdirectory(test)
