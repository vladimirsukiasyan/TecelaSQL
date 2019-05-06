#include <utility>

#include <utility>

//
// Created by vladimir on 07.04.19.
//

#ifndef TECELASQL_HASHTABLE_H
#define TECELASQL_HASHTABLE_H

#include <string>
#include <vector>
#include <map>
#include <cstddef>
#include "HashNode.h"

const size_t DEFAULT_SIZE = 8;

size_t Hash(const std::string &s, size_t size);

class HashTable {
public:
    explicit HashTable(size_t size = DEFAULT_SIZE)
            : table(size, nullptr), size(0) {}

    ~HashTable() {
        //
    }

    bool Add(const std::string &key,
             long long exptime,
             long long length,
             std::byte *value
            );

    bool Delete(const std::string &key);

    bool Has(const std::string &key);

private:
    std::vector<HashNode *> table;
    size_t size;
};

#endif //TECELASQL_HASHTABLE_H
