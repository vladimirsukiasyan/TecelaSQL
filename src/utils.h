//
// Created by dmitry on 19.05.19.
//

#ifndef TECELASQL_UTILS_H
#define TECELASQL_UTILS_H

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

extern HashTable *pTable;

#endif //TECELASQL_UTILS_H
