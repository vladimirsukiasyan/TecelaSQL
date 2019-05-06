//
// Created by dmitry on 01.05.19.
//

#include "HashTable.h"

const size_t HASH_1 = 11;
const size_t HASH_2 = 17;
const double MAX_ALPHA = 0.75;

bool HashTable::Has(const std::string &key) {
    size_t hash = Hash(key, table.size());

    HashNode *node = table[hash];
    while (node != nullptr && node->key != key) {
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
    while (node != nullptr && node->key != key) {
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

long long HashTable::GetLifetime(const std::string &key) {
    size_t hash = Hash(key , table.size());
    HashNode *node = table[hash];
    while (node != nullptr && node->key != key){
        node = node->next;
    }
    if (node == nullptr)
        throw ("No such key in table");
    return node->exptime;
}

std::string HashTable::Get(const std::string &key) {
    size_t hash = Hash(key, table.size());

    HashNode *node = table[hash];
    while (node != nullptr && node->key != key) {
        node = node->next;
    }

    if (node == nullptr)
        return "error";

    else {
        std::string s ="Key: " + node->key + " length: " + std::to_string(node->length) +" exptime: " + std::to_string(node->exptime) + " value: " + (char*)node->value;
        return s;
    }
}

bool HashTable::Set(const std::string &key, long long exptime, long long length, std::byte *value) {
    size_t hash = Hash(key, table.size());

    HashNode *node = table[hash];
    while (node != nullptr && node->key != key) {
        node = node->next;
    }

    if (node == nullptr)
        return false;
    else{
        node->exptime = exptime;
        node->length = length;
        node->value = value;
        return true;
    }

}

//TODO double hashing realization in add, del, has
size_t Hash1(const std::string &s, size_t size) {
    size_t hash = 0;
    for (char i : s) {
        hash = hash * HASH_1 + i;
    }
    return hash % size;
}

size_t Hash2(const std::string &s, size_t size ){
   size_t hash = 0;
    for (char i : s) {
        hash = hash * HASH_2 + i;
    }
    return (2*hash+1) % size;
}

size_t DoubleHash(size_t h1, size_t h2, size_t i, size_t size){
    if (size != 0){
        return (h1 + i * h2) % size;
    } else {
        return 0;
    }
}
