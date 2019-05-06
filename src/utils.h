//
// Created by vladimir on 27.04.19.
//

#ifndef TECELASQL_UTILS_H
#define TECELASQL_UTILS_H

#include <boost/asio/ip/tcp.hpp>
#include "HashTable/HashTable.h"

enum class METHOD {
    GET,
    ADD,
    SET,
    DELETE,
    INCR,
    DECR,
    DISCONNECT,
    TOUCH,
    FLUSH_ALL
};

class InvalidTextLineException: public std::exception{

    const char* what() const throw() override {
        return "Invalid TextLine!";
    }
};



//HashTable *pTable = nullptr;

#endif //TECELASQL_UTILS_H
