#include <gtest/gtest.h>
#include "../src/Server/Server.h"
#include "../src/HashTable/HashTable.h"

TEST(basic_check, test_eq){
    EXPECT_EQ(0,1);
}
TEST(TestHashTable, HashTable){
    HashTable<int, int> table;
    EXPECT_TRUE(table.Add(1120,11,10));
    EXPECT_TRUE(table.Has(1120));
    EXPECT_EQ(10,table.GetLifetime(1120));
    EXPECT_TRUE(table.Delete(1120));
    EXPECT_FALSE(table.Has(1120));

}

int main(int argc, char **argv) {
    // The following line must be executed to initialize Google Mock
    // (and Google Test) before running the tests.
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}