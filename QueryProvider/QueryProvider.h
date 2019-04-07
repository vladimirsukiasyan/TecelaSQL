//
// Created by vladimir on 07.04.19.
//

#ifndef TECELASQL_QUERYPROVIDER_H
#define TECELASQL_QUERYPROVIDER_H


#include <string>

class QueryProvider {

public:
    void addValue(std::string &key, std::string value);

    void setValue(std::string& key, std::string value);

    void replace(std::string& key, std::string value);

    std::string getValue(std::string &key);

    void deleteValue(std::string &key);

    void flushAll();


    //atomic operation
    void incr(std::string &key);
    //atomic operation
    void decr(std::string &key);

};


#endif //TECELASQL_QUERYPROVIDER_H
