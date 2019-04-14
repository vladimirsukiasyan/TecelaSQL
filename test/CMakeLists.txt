cmake_minimum_required(VERSION 3.13)
project(TEST_PROJECT)

add_executable(TestAllProject main.cpp)

target_link_libraries(TestAllProject gtest gtest_main)
