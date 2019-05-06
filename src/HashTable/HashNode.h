//
// Created by vladimir on 15.04.19.
//

#ifndef TECELASQL_HASHNODE_H
#define TECELASQL_HASHNODE_H

#include <cstddef>
#include <string>

class HashNode
{
public:
    HashNode() : next(nullptr) {}
    HashNode(std::string key, long long exptime, long long length, std::byte *value, HashNode *next)
            : key(std::move(key)),
              exptime(exptime),
              length(length),
              value(value),
              next(next)
              {}
    std::string key;
    long long exptime;
    long long length;
    std::byte * value;
    HashNode *next;
};

#endif //TECELASQL_HASHNODE_H
