cmake_minimum_required(VERSION 3.13)
project(TEST_PROJECT)

enable_testing()

add_executable(TestHashTable testing.cpp)

target_link_libraries(TestHashTable gtest gtest_main)

add_test(
        NAME TestHashtable
        COMMAND TestHashTable
)
