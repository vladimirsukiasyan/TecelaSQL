//
// Created by vladimir on 14.04.19.
//

#include "GetCommand.h"

std::string GetCommand::execute() {
    std::lock_guard<std::recursive_mutex> lock(_mx);
    ERRORS errors;
    std::string answer = HashTable::getInstance()->Get(this->key, errors);
    if (errors == ERRORS::NOT_FOUND) {
        throw NotFoundKeyException();
    }
    else{
        return answer;
    }
}

std::string GetCommand::toStr() {
    ERRORS errors;
    std::string answer = "Get " + HashTable::getInstance()->Get(this->key, errors);
    return answer;
}