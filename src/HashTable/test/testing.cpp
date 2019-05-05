//
// Created by dmitry on 03.05.19.
//
#include <gtest/gtest.h>
#include "../HashTable.h"

TEST(HashTable, Add) {
    HashTable table;
    EXPECT_TRUE(table.Add("1", 11, 10, 0x62ff78));
    EXPECT_TRUE(table.Add("2", 12, 11, 0x63ff78));
    EXPECT_FALSE(table.Add("1", 11, 10, 0x62ff78));
    EXPECT_FALSE(table.Add("2", 12, 11, 0x63ff78));

}

TEST(HashTable, Delete) {
    HashTable table;
    EXPECT_FALSE(table.Delete("1"));
    table.Add("1", 11, 10, 0x62ff78);
    EXPECT_TRUE(table.Delete("1"));
    EXPECT_FALSE(table.Delete("1"));
}

TEST(HashTable, Has) {
    HashTable table;
    EXPECT_FALSE(table.Has("1"));
    table.Add("1", 11, 10, 0x62ff78);
    EXPECT_TRUE(table.Has("1"));
    EXPECT_FALSE(table.Has("2"));
}

TEST(HashTable, GetLifeTime) {
    HashTable table;
    table.Add("1", 11, 10, 0x62ff78);
    EXPECT_EQ(table.GetLifetime("1"), 10);
    table.Add("212", 11, 1212, 0x63ff78);
    EXPECT_EQ(table.GetLifetime("212"), 1212);
}

int main(int argc, char **argv) {
    // The following line must be executed to initialize Google Mock
    // (and Google Test) before running the tests.
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}