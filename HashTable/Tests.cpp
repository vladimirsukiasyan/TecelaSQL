//
// Created by ivan on 08.04.19.
//
#include "HashTable.h"

void TestHas()
{
    HashTable HT;
    HT.Add("key");
    assert(HT.has("key"));
    assert(HT.has("keeeeey")==false);
    std::cout << "All tests in TestHas() are OK";
}

void TestAdd()
{
    HashTable HT;
    assert(HT.Add("key"));
    assert(HT.Add("key")==false);
    std::cout << "All tests in TestAdd() are OK";
}

void TestDelete()
{
    HashTable HT;
    HT.Add("keeey");
    assert(HT.Delete("key")==false);
    assert(HT.Delete("keeey"));
    std::cout << "All tests in TestDelete() are OK";
}

