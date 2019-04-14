//
// Created by vladimir on 07.04.19.
//

#ifndef TECELASQL_HASHTABLE_H
#define TECELASQL_HASHTABLE_H


#include <iostream>
#include <vector>

const size_t DEFAULT_SIZE = 8;

template <typename K, typename V>
struct HashNode
{
    HashNode() : next(nullptr) {}
    HashNode(const K &key, const V &value, HashNode<K,V> *next)
            : key(key),
            next(next),
            value(value)
            {}
    K key;
    V value;
    HashNode<K,V> *next;
};

size_t Hash(const std::string &s, size_t size);

template <typename K, typename V>
class HashTable
{
public:
    explicit HashTable(size_t size = DEFAULT_SIZE)
            : table(size, nullptr), size(0) {}

    ~HashTable();

    bool Add(const K &key, const V &data);

    bool Delete(const K &key);

    bool Has(const K &key);

private:
    std::vector<HashNode<K,V>*> table;
    size_t size;
};


template<typename K, typename V>
bool HashTable<K,V>::Has(const K &key) {
    size_t hash = Hash(key, table.size());

    HashNode<K,V> *node = table[hash];
    while (node != nullptr && node->key != key)
    {
        node = node->next;
    }

    return node != nullptr;
}

template<typename K,typename V>
bool HashTable<K,V>::Add(const K &key, const V &value) {

    size_t hash = Hash(key, value, table.size());

    HashNode<K,V> *node = table[hash];
    while (node != nullptr && node->key != key)
    {
        node = node->next;
    }

    if (node != nullptr)
        return false;

    table[hash] = new HashNode<K,V>(key, value, table[hash]);
    size++;
    return true;
}

template<typename K, typename V>
bool HashTable<K,V>::Delete(const K &key) {
    size_t hash = Hash(key, table.size());

    HashNode<K,V> *prevNode = nullptr;
    HashNode<K,V> *node = table[hash];
    while (node != nullptr && node->key != key)
    {
        prevNode = node;
        node = node->next;
    }

    if (node == nullptr)
        return false;

    if (prevNode == nullptr)
    {
        table[hash] = node->next;
    }
    else
    {
        prevNode->next = node->next;
    }

    delete node;
    size--;
    return true;
}

template<typename K, typename V>
HashTable<K,V>::~HashTable() {

}


#endif //TECELASQL_HASHTABLE_H
