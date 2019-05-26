//
// Created by vladimir on 14.04.19.
//

#include "DeleteCommand.h"

std::string DeleteCommand::execute() {
    std::lock_guard<std::recursive_mutex> lock(_mx);

    ERRORS errors;
    HashTable::getInstance()->Delete(this->key, errors);
    if (errors == ERRORS::NOT_FOUND){
        throw NotFoundKeyException();
    } else{
        return "DELETED";
    }

}

std::string DeleteCommand::toStr() {
    //TODO сделай нормально!
//    std::string answer = "Del " + HashTable::getInstance()->Get(this->key);
//    return answer;
}