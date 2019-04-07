//
// Created by vladimir on 07.04.19.
//

#ifndef TECELASQL_HASHTABLE_H
#define TECELASQL_HASHTABLE_H


#include <iostream>
#include <vector>

const size_t DEFAULT_SIZE = 8;
const size_t RESIZE_FACTOR = 2;
const size_t MAX_ALPHA = 3;

template <typename T>
struct HashNode
{
    HashNode() : next(nullptr) {}
    HashNode(const T &key, HashNode<T> *next)
            : key(key), next(next){}
    T key;
    HashNode<T> *next;
};

size_t Hash(const std::string &s, size_t size);

template <typename T>
class HashTable
{
public:
    explicit HashTable(size_t size = DEFAULT_SIZE)
            : table(size, nullptr), size(0) {}

    ~HashTable();

    bool Add(const T &key);

    bool Delete(const T &key);

    bool Has(const T &key);

private:
    std::vector<HashNode<T>*> table;
    size_t size;

    void grow();
};


template<typename T>
bool HashTable<T>::Has(const T &key) {
    size_t hash = Hash(key, table.size());

    HashNode<T> *node = table[hash];
    while (node != nullptr && node->key != key)
    {
        node = node->next;
    }

    return node != nullptr;
}

template<typename T>
bool HashTable<T>::Add(const T &key) {
    if (size > MAX_ALPHA * table.size())
        grow();

    size_t hash = Hash(key, table.size());

    HashNode<T> *node = table[hash];
    while (node != nullptr && node->key != key)
    {
        node = node->next;
    }

    if (node != nullptr)
        return false;

    table[hash] = new HashNode<T>(key, table[hash]);
    size++;
    return true;
}

template<typename T>
bool HashTable<T>::Delete(const T &key) {
    size_t hash = Hash(key, table.size());

    HashNode<T> *prevNode = nullptr;
    HashNode<T> *node = table[hash];
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

template<typename T>
void HashTable<T>::grow() {
    std::vector<HashNode<T>*> newTable(table.size() * RESIZE_FACTOR, nullptr);

    for (size_t i = 0; i < table.size(); i++)
    {
        HashNode<T> *node = table[i];
        while (node != nullptr)
        {
            size_t newHash = Hash(node->key, newTable.size());
            HashNode<T> *tmp = node->next;
            node->next = newTable[newHash];
            newTable[newHash] = node;
            node = tmp;
        }
    }
    table = std::move(newTable);
}

template<typename T>
HashTable<T>::~HashTable() {

}


#endif //TECELASQL_HASHTABLE_H
