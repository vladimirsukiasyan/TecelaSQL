//
// Created by vladimir on 14.04.19.
//

#include "SetCommand.h"

std::string SetCommand::execute() {
    ERRORS errors;
    HashTable::getInstance()->Set(this->key, this->exptime, this->length, this->value, errors);
    if (errors == ERRORS::NOT_FOUND) {
        throw NotFoundKeyException();
    }
    else if(errors == ERRORS::NOT_ENOUGH_MEMORY){
        throw NotEnoughMemoryException();
    }
    else{
        //CacheManager
        return "STORED";
    }
};

std::string SetCommand::toStr() {
    std::string answer =
            "Set " + this->key + " " + std::to_string(this->exptime) + " " + std::to_string(this->length) + " " +
            (char *) this->value;
    return answer;
}