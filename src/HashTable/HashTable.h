//
// Created by dmitry on 01.05.19.
//
#ifndef TECELASQL_HASHTABLE_H
#define TECELASQL_HASHTABLE_H

#include <cstddef>
#include <utility>
#include <string>
#include <vector>
#include <map>
#include "HashNode.h"
#include <iostream>
#include "../utils.h"

const size_t DEFAULT_SIZE = 8;
const size_t DEFAULT_LENGTH = 1024;

size_t Hash1(const std::string &s, size_t size);

size_t Hash2(const std::string &s, size_t size);

size_t DoubleHash(size_t h1, size_t h2, size_t i, size_t size);

class HashTable {
public:
    explicit HashTable(size_t size = DEFAULT_SIZE, size_t sizeBuffer = DEFAULT_LENGTH)
            : size(0), sizeBuffer(1024) {
        table = new HashNode[sizeBuffer];
    }

    ~HashTable() {
        for (int i = 0; i < size; i++)
            delete table[i];
    }

    bool Add(const std::string &key,
             long long exptime,
             long long length,
             std::byte *value
    );

    bool Set(const std::string &key,
             long long exptime,
             long long length,
             std::byte *value
    );

    bool Delete(const std::string &key);

    bool Has(const std::string &key);

    std::string Get(const std::string &key);

    long long GetLifetime(const std::string &key);

private:
    HashNode *table;
    size_t size;
    size_t sizeBuffer;
};

#endif //TECELASQL_HASHTABLE_H