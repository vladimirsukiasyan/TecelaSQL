//
// Created by vladimir on 07.04.19.
//

#ifndef TECELASQL_HASHTABLE_H
#define TECELASQL_HASHTABLE_H


#include <iostream>
#include <vector>
#include <string>

const size_t DEFAULT_SIZE = 8;

template <typename K>
size_t Hash(const K &key, size_t size);

template<typename V>
struct HashNode {
    HashNode() : next(nullptr) {}

    HashNode(const std::string &key, const V &value, HashNode<V> *next, int lifetime)
            : key(key),
              next(next),
              value(value),
              lifetime(lifetime) {}

    std::string key;
    V value;
    int lifetime;
    HashNode<V> *next;
};

template<typename V>
class HashTable {
public:
    explicit HashTable(size_t size = DEFAULT_SIZE)
            : table(size, nullptr), size(0) {}

    ~HashTable();

    bool Add(const std::string &key, const V &data, int lifetime);

    bool Delete(const std::string &key);

    bool Has(const std::string &key);

    int GetLifetime(const std::string &key);

private:
    std::vector<HashNode<V> *> table;
    size_t size;
    size_t lifetime;
};


template<typename V>
bool HashTable<V>::Has(const std::string &key) {
    size_t hash = Hash(key, table.size());

    HashNode<V> *node = table[hash];
    while (node != nullptr && node->key != key) {
        node = node->next;
    }

    return node != nullptr;
}

template<typename V>
bool HashTable<V>::Add(const std::string &key, const V &value, int lifetime) {

    size_t hash = Hash(key, table.size());

    HashNode<V> *node = table[hash];
    while (node != nullptr && node->key != key) {
        node = node->next;
    }

    if (node != nullptr)
        return false;

    table[hash] = new HashNode<V>(key, value, table[hash], lifetime);
    size++;
    return true;
}

template<typename V>
bool HashTable<V>::Delete(const std::string &key) {
    size_t hash = Hash(key, table.size());

    HashNode<V> *prevNode = nullptr;
    HashNode<V> *node = table[hash];
    while (node != nullptr && node->key != key) {
        prevNode = node;
        node = node->next;
    }

    if (node == nullptr)
        return false;

    if (prevNode == nullptr) {
        table[hash] = node->next;
    } else {
        prevNode->next = node->next;
    }

    delete node;
    size--;
    return true;
}

template<typename V>
int HashTable<V>::GetLifetime(const std::string &key) {
    size_t hash = Hash(key, table.size());

    HashNode<V> *node = table[hash];
    while (node != nullptr && node->key != key) {
        node = node->next;
    }
    if (node == nullptr)
        throw ("No such key in table");
    return node->lifetime;
}


template<typename V>
HashTable<V>::~HashTable() {

}
size_t Hash(const std::string &key, size_t size) {
    size_t hash = 0;
    for (size_t i = 0; i < key.size(); i++) {
        hash = hash * 73 + key[i];
    }
    return hash % size;
}

#endif //TECELASQL_HASHTABLE_H
