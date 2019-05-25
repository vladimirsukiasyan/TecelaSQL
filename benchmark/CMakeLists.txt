cmake_minimum_required(VERSION 3.13)
project(TecelaSQLClient)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED COMPONENTS system filesystem thread)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(TecelaSQLBenchmarkt Benchmark.cpp)
    target_link_libraries(TecelaSQLBenchmarkt ${Boost_LIBRARIES})
endif ()