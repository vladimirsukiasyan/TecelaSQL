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
#include "../codeErrors.h"


const size_t DEFAULT_SIZE = 1024;

size_t Hash1(const std::string &s, size_t size);

size_t Hash2(const std::string &s, size_t size);

size_t DoubleHash(size_t h1, size_t h2, size_t i, size_t size);


class HashTable {

    HashNode **_table;
    size_t _capacity;

public:
    explicit HashTable(size_t capacity = DEFAULT_SIZE)
            : _capacity(capacity) {
        _table= new HashNode*[capacity];
        for (int i = 0; i < capacity; ++i) {
            _table[i] = nullptr;
        }

    }

    ~HashTable() {
        for (int i = 0; i < _capacity; i++)
            delete _table[i];
    }

    void Add(const std::string &key,
               long long exptime,
               long long length,
               std::byte *value,
               ERRORS &errors
    );

    void Set(const std::string &key,
               long long exptime,
               long long length,
               std::byte *value,
               ERRORS &errors
    );

    void Delete(const std::string &key, ERRORS &errors);

    void Has(const std::string &key, ERRORS &errors);

    std::string Get(const std::string &key, ERRORS &errors);

    long long GetLifetime(const std::string &key, ERRORS &errors);
};

#endif //TECELASQL_HASHTABLE_H