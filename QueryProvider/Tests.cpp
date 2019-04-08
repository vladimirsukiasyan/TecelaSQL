//
// Created by Дарья Береговая on 2019-04-08.
//

#include "Tests.h"
#include "QueryProvider.h"

void RUN_ALL_TESTS(std::string&, std::string);

int main(){
    RUN_ALL_TESTS();
    return 0;
}

void TestAddValue(std::string &key, std::string value){
    try{
        addValue(key, string);
    }
    catch(std::exception &exception){
        throw excepton;
    }
}

void TestSetValue(std::string &key, std::string value){
    try{
        setValue(key, string);
    }
    catch(std::exception &exception){
        throw excepton;
    }
}

void TestReplace(std::string &key, std::string value){
    try{
        replace(key, string);
    }
    catch(std::exception &exception){
        throw excepton;
    }
}

void TestGetValue(std::string &key){
    assert(getyValue(key));
}

void TestDeleteValue(std::string &key){
    try{
        deleteValue(key);
    }
    catch(std::exception &exception){
        throw excepton;
    }
}

void TestFlushAll(){
    try{
        flushAll();
    }
    catch(std::exception &exception){
        throw excepton;
    }
}

void RUN_ALL_TEST(std::string &key, string:: value){
    TestAddValue(key, value);
    TestDeleteValue(key);
    TestFlushAll();
    TestGetValue(key);
    TestReplace(key, value);
    TestSetValue(key, value);
}



