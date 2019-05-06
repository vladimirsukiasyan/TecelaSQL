//
// Created by vladimir on 15.04.19.
//

#include "HashTable.h"

bool HashTable::Has(const std::string &key) {
    size_t hash = Hash(key, table.size());

    HashNode* node = table[hash];
    while (node != nullptr && node->key != key)
    {
        node = node->next;
    }

    return node != nullptr;
}

bool HashTable::Add(const std::string &key,
                    long long exptime,
                    long long length,
                    std::byte *value) {

    size_t hash = Hash(key, table.size());

    HashNode *node = table[hash];
    while (node != nullptr && node->key != key)
    {
        node = node->next;
    }

    if (node != nullptr)
        return false;

    table[hash] = new HashNode(
            key,
            exptime,
            length,
            value,
            table[hash]
            );
    size++;
    return true;
}

bool HashTable::Delete(const std::string &key) {
    size_t hash = Hash(key, table.size());

    HashNode *prevNode = nullptr;
    HashNode *node = table[hash];
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


//TODO double hashing
size_t Hash(const std::string &s, size_t size)
{
    size_t hash = 0;
    for (char i : s) {
        hash = hash * 73 + i;
    }
    return hash % size;
}