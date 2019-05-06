//git
// Created by dmitry on 03.05.19.
//
#include <gtest/gtest.h>
#include "../HashTable.h"

TEST(HashTable, Add) {
    HashTable table;
    std::byte value1[3], value2[3];
    std::string s1 = "123", s2 = "124";
    for (size_t i = 0; i < 3; i++) {
        value1[i] = (std::byte) s1[i];
        value2[i] = (std::byte) s2[i];
    }
    EXPECT_TRUE(table.Add("1", 11, 10, value1));
    EXPECT_TRUE(table.Add("2", 12, 11, value2));
    EXPECT_FALSE(table.Add("1", 11, 10, value1));
    EXPECT_FALSE(table.Add("2", 12, 11, value2));

}

TEST(HashTable, Delete) {
    HashTable table;
    std::byte value1[3];
    std::string s1 = "123";
    for (size_t i = 0; i < 3; i++) {
        value1[i] = (std::byte) s1[i];
    }
    EXPECT_FALSE(table.Delete("1"));
    table.Add("1", 11, 10, value1);
    EXPECT_TRUE(table.Delete("1"));
    EXPECT_FALSE(table.Delete("1"));
}

TEST(HashTable, Has) {
    HashTable table;
    std::byte value1[3];
    std::string s1 = "123";
    for (size_t i = 0; i < 3; i++) {
        value1[i] = (std::byte) s1[i];
    }
    EXPECT_FALSE(table.Has("1"));
    table.Add("1", 11, 10, value1);
    EXPECT_TRUE(table.Has("1"));
    EXPECT_FALSE(table.Has("2"));
}

TEST(HashTable, GetLifeTime) {
    HashTable table;
    std::byte value1[3], value2[3];
    std::string s1 = "123", s2 = "124";
    for (size_t i = 0; i < 3; i++) {
        value1[i] = (std::byte) s1[i];
        value2[i] = (std::byte) s2[i];
    }
    table.Add("1", 11, 10, value1);
    EXPECT_EQ(table.GetLifetime("1"), 10);
    table.Add("212", 11, 1212, value2);
    EXPECT_EQ(table.GetLifetime("212"), 1212);
}

int main(int argc, char **argv) {
    // The following line must be executed to initialize Google Mock
    // (and Google Test) before running the tests.
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}