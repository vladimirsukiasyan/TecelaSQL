//
// Created by dmitry on 14.04.19.
//

#include "AddCommand.h"

std::string AddCommand::execute() {
    std::lock_guard<std::recursive_mutex> lock(_mx);
    ERRORS errors;
    HashTable::getInstance()->Add(this->key, this->exptime, this->length, this->value, errors);
    if (errors == ERRORS::NOT_ENOUGH_MEMORY) {
        throw NotEnoughMemoryException();
    } else{
        // Вызвать setTimer CacheManager
        return "STORED";
    }
}

std::string AddCommand::toStr() {
    std::string answer =
            "Add " + this->key + " " + std::to_string(this->exptime) + " " + std::to_string(this->length) + " " + (char *) this->value;
    return answer;
}