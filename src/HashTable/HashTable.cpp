#include "HashTable.h"

const size_t HASH_1 = 11;
const size_t HASH_2 = 17;
const double MAX_ALPHA = 0.75;

enum ERRORS HashTable::Has(const std::string &key) {
    size_t hash1 = Hash1(key, sizeBuffer);
    size_t hash2 = Hash2(key, sizeBuffer);
    size_t hash = DoubleHash(hash1, hash2, 0, sizeBuffer);
    int i = 0;
    while (table[hash] != nullptr && i < sizeBuffer) {
        if (table[hash]->getKey() == key && !table[hash]->isDel()) {
            return ERRORS::SUCCESS;
        }

        hash = DoubleHash(hash1, hash2, i + 1, sizeBuffer);
        i++;
    }

    return ERRORS::NOTFOUND;
}

enum ERRORS HashTable::Add(const std::string &key,
                           long long exptime,
                           long long length,
                           std::byte *value) {

    size_t hash1 = Hash1(key, sizeBuffer);
    size_t hash2 = Hash2(key, sizeBuffer);
    size_t hash = DoubleHash(hash1, hash2, 0, sizeBuffer);
    int firstD = -1,
            i = 0;
    while (table[hash] != nullptr && i < sizeBuffer) {
        if (table[hash]->getKey() == key && !table[hash]->isDel())
            return ERRORS::NOTFOUND;
        if (table[hash]->isDel() && firstD < 0)
            firstD = hash;
        hash = DoubleHash(hash1, hash2, i + 1, sizeBuffer);
        i++;
    }
    if (firstD < 0) {
        table[hash] = new HashNode(key,
                                   exptime,
                                   length,
                                   value,
                                   table[hash]);
    } else {
        table[firstD]->setKey(key);
        table[firstD]->setNotDel();
    }
    size++;
    return ERRORS::SUCCESS;
}

enum ERRORS HashTable::Delete(const std::string &key) {
    size_t hash1 = Hash1(key, sizeBuffer);
    size_t hash2 = Hash2(key, sizeBuffer);
    size_t hash = DoubleHash(hash1, hash2, 0, sizeBuffer);
    int i = 0;
    while (table[hash] != nullptr && i < sizeBuffer) {
        if (table[hash]->getKey() == elem && !table[hash]->isDel()) {
            table[hash]->setDel();
            size--;
            return ERRORS::SUCCESS;
        }
        hash = DoubleHash(hash1, hash2, i + 1, sizeBuffer);
        i++;
    }

    return ERRORS::NOTFOUND;
}

enum ERRORS HashTable::GetLifetime(const std::string &key, long long &value) {
    size_t hash1 = Hash1(key, sizeBuffer);
    size_t hash2 = Hash2(key, sizeBuffer);
    size_t hash = DoubleHash(hash1, hash2, 0, sizeBuffer);
    int i = 0;
    while (table[hash] != nullptr && i < sizeBuffer) {
        if (table[hash]->getKey() == key && !table[hash]->isDel()) {
            value = table[hash]->exptime;
            return ERRORS::SUCCESS;
        }
        hash = DoubleHash(hash1, hash2, i + 1, sizeBuffer);
        i++;
    }

    return ERRORS::NOTFOUND;
}

enum ERRORS HashTable::Get(const std::string &key, std::string &value) {
    size_t hash1 = Hash1(key, sizeBuffer);
    size_t hash2 = Hash2(key, sizeBuffer);
    size_t hash = DoubleHash(hash1, hash2, 0, sizeBuffer);
    int i = 0;
    while (table[hash] != nullptr && i < sizeBuffer) {
        if (table[hash]->getKey() == key && !table[hash]->isDel()) {
            value = "Key: " + table[hash]->key + " length: " + std::to_string(table[hash]->length) + " exptime: " +
                    std::to_string(table[hash]->exptime) + " value: " + (char *) table[hash]->value;
            return ERRORS::SUCCESS;
        }
        hash = DoubleHash(hash1, hash2, i + 1, sizeBuffer);
        i++;
    }
    return ERRORS::NOTFOUND;
}

enum ERRORS HashTable::Set(const std::string &key, long long exptime, long long length, std::byte *value) {
    size_t hash1 = Hash1(key, sizeBuffer);
    size_t hash2 = Hash2(key, sizeBuffer);
    size_t hash = DoubleHash(hash1, hash2, 0, sizeBuffer);
    int i = 0;
    while (table[hash] != nullptr && i < sizeBuffer) {
        if (table[hash]->getKey() == key && !table[hash]->isDel()) {
            table[hash]->key = key;
            table[hash]->length = length;
            table[hash]->exptime = exptime;
            table[hash]->value = value;
            return ERRORS::SUCCESS;
        }
        hash = DoubleHash(hash1, hash2, i + 1, sizeBuffer);
        i++;
    }
    return ERRORS::NOTFOUND;

}

size_t Hash1(const std::string &s, size_t size) {
    size_t hash = 0;
    for (char i : s) {
        hash = hash * HASH_1 + i;
    }
    return hash % size;
}

size_t Hash2(const std::string &s, size_t size) {
    size_t hash = 0;
    for (char i : s) {
        hash = hash * HASH_2 + i;
    }
    return (2 * hash + 1) % size;
}

size_t DoubleHash(size_t h1, size_t h2, size_t i, size_t size) {
    if (size != 0) {
        return (h1 + i * h2) % size;
    } else {
        return 0;
    }
}
