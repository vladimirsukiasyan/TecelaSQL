//
// Created by dmitry on 09.05.19.
//

#include <gtest/gtest.h>
#include "../Query.h"

TEST(Query, parseHeadLine) {
    Query obj;
    std::string cmd = "Add 111 10 3 112";
    obj.parseHeadLine(cmd);
    auto newcmd = (AddCommand *) obj.getCommand();
    EXPECT_EQ("Add 111 10 3 112", newcmd->toStr());
    cmd = "Set 111 11 4 1112";
    obj.parseHeadLine(cmd);
    auto newcmd1 = (SetCommand *) obj.getCommand();
    EXPECT_EQ("Set 111 4 1112", newcmd1->toStr());
    cmd = "Get 111";
    obj.parseHeadLine(cmd);
    auto newcmd2 = (GetCommand *) obj.getCommand();
    EXPECT_EQ("Key: 111 length: 4 exptime: 111 value: 1112", newcmd2->toStr());
    cmd = "Del 111";
    obj.parseHeadLine(cmd);
    auto newcmd3 = (DeleteCommand *) obj.getCommand();
    EXPECT_EQ("Key: 111 length: 4 exptime: 111 value: 1112", newcmd3->toStr());
}

int main(int argc, char **argv) {
    // The following line must be executed to initialize Google Mock
    // (and Google Test) before running the tests.
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}