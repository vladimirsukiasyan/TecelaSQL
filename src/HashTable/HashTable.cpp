#include "HashTable.h"

const size_t HASH_1 = 11;
const size_t HASH_2 = 17;
const double MAX_ALPHA = 0.75;

void HashTable::Has(const std::string &key, ERRORS &errors) {
    size_t hash1 = Hash1(key, _capacity);
    size_t hash2 = Hash2(key, _capacity);
    size_t hash = DoubleHash(hash1, hash2, 0, _capacity);
    int i = 0;
    while (_table[hash] != nullptr && i < _capacity) {
        if (_table[hash]->getKey() == key && _table[hash]->getKey() != "DELETED") {
            errors = ERRORS::SUCCESS;
        }

        hash = DoubleHash(hash1, hash2, i + 1, _capacity);
        i++;
    }

    errors = ERRORS::NOTFOUND;
}

void HashTable::Add(const std::string &key,
                    long long exptime,
                    long long length,
                    std::byte *value,
                    ERRORS &errors) {

    size_t hash1 = Hash1(key, _capacity);
    size_t hash2 = Hash2(key, _capacity);
    size_t hash = DoubleHash(hash1, hash2, 0, _capacity);
    int firstD = -1,
            i = 0;
    while (_table[hash] != nullptr && i < _capacity) {
        if (_table[hash]->getKey() == key && _table[hash]->getKey() != "DELETED")
            errors = ERRORS::NOTFOUND;
        if (_table[hash]->isDel() && firstD < 0)
            firstD = hash;
        hash = DoubleHash(hash1, hash2, i + 1, _capacity);
        i++;
    }
    if (firstD < 0) {
        _table[hash] = new HashNode(key,
                                    exptime,
                                    length,
                                    value,
                                    _table[hash]);
    } else {
        _table[firstD]->setKey(key);
    }
    errors = ERRORS::SUCCESS;
}

void HashTable::Delete(const std::string &key, ERRORS &errors) {
    size_t hash1 = Hash1(key, _capacity);
    size_t hash2 = Hash2(key, _capacity);
    size_t hash = DoubleHash(hash1, hash2, 0, _capacity);
    int i = 0;
    while (_table[hash] != nullptr && i < _capacity) {
        if (_table[hash]->getKey() == key && _table[hash]->getKey() != "DELETED") {
            HashNode *node = new HashNode();
            node->setKey("DELETED");
            delete _table[hash];
            _table[hash] = node;
            errors = ERRORS::SUCCESS;
        }
        hash = DoubleHash(hash1, hash2, i + 1, _capacity);
        i++;
    }

    errors = ERRORS::NOTFOUND;
}

long long  HashTable::GetLifetime(const std::string &key, ERRORS &errors) {
    size_t hash1 = Hash1(key, _capacity);
    size_t hash2 = Hash2(key, _capacity);
    size_t hash = DoubleHash(hash1, hash2, 0, _capacity);
    int i = 0;
    while (_table[hash] != nullptr && i < _capacity) {
        if (_table[hash]->getKey() == key && !_table[hash]->isDel()) {
            errors = ERRORS::SUCCESS;
            return  _table[hash]->getExptime();

        }
        hash = DoubleHash(hash1, hash2, i + 1, _capacity);
        i++;
    }

    errors = ERRORS::NOTFOUND;
}
//TODO Вукидывать exception во всем HashTable
std::string HashTable::Get(const std::string &key, ERRORS &errors) {
    size_t hash1 = Hash1(key, _capacity);
    size_t hash2 = Hash2(key, _capacity);
    size_t hash = DoubleHash(hash1, hash2, 0, _capacity);
    int i = 0;
    while (_table[hash] != nullptr && i < _capacity) {
        if (_table[hash]->getKey() == key && _table[hash]->getKey() != "DELETED") {
            errors = ERRORS::SUCCESS;
            return "Key: " + _table[hash]->getKey() + " length: " + std::to_string(_table[hash]->getLength()) +
                   " exptime: " +
                   std::to_string(_table[hash]->getExptime()) + " value: " + (char *) _table[hash]->getValue();
        }
        hash = DoubleHash(hash1, hash2, i + 1, _capacity);
        i++;
    }
    errors = ERRORS ::NOTFOUND;
    return "";
}

void HashTable::Set(const std::string &key, long long exptime, long long length, std::byte *value, ERRORS &errors) {
    size_t hash1 = Hash1(key, _capacity);
    size_t hash2 = Hash2(key, _capacity);
    size_t hash = DoubleHash(hash1, hash2, 0, _capacity);
    int i = 0;
    while (_table[hash] != nullptr && i < _capacity) {
        if (_table[hash]->getKey() == key && _table[hash]->getKey() != "DELETED") {
            _table[hash]->setKey(key);
            _table[hash]->setLength(length);
            _table[hash]->setExptime(exptime);
            _table[hash]->setValue(value);
            errors = ERRORS::SUCCESS;
        }
        hash = DoubleHash(hash1, hash2, i + 1, _capacity);
        i++;
    }
    errors = ERRORS::NOTFOUND;

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