//
// Created by dmitry on 05.05.19.
//

#ifndef TECELASQL_HASHNODE_H
#define TECELASQL_HASHNODE_H

#include <cstddef>
#include <string>

class HashNode {
public:
    HashNode() : next(nullptr) {}

    HashNode(std::string key, long long exptime, long long length, std::byte *value, HashNode *next)
            : key(std::move(key)),
              exptime(exptime),
              length(length),
              value(value),
              next(next) {}


    const std::string &getKey() {
        return key;
    }

    bool isDel() const {
        return del;
    }

    void setDel() {
        del = true;
    }

    void setNotDel() {
        del = false;
    }

    void setKey(const std::string &elem) {
        key = elem;
    }

private:
    std::string key;
    long long exptime;
    long long length;
    std::byte *value;
    HashNode *next;
    bool del;
};

#endif //TECELASQL_HASHNODE_H