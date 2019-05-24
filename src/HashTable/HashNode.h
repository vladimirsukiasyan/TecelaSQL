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

private:
    std::string key;
public:
    const std::string &getKey() const {
        return key;
    }

    void setKey(const std::string &key) {
        HashNode::key = key;
    }

    long long int getExptime() const {
        return exptime;
    }

    void setExptime(long long int exptime) {
        HashNode::exptime = exptime;
    }

    long long int getLength() const {
        return length;
    }

    void setLength(long long int length) {
        HashNode::length = length;
    }

    std::byte *getValue() const {
        return value;
    }

    void setValue(std::byte *value) {
        HashNode::value = value;
    }

    bool isDel() const {
        return del;
    }

    void setDel(bool del) {
        HashNode::del = del;
    }

private:
    long long exptime;
    long long length;
    std::byte *value;
    HashNode *next;
    bool del;
};

#endif //TECELASQL_HASHNODE_H