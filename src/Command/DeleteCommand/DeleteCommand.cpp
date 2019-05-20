//
// Created by vladimir on 14.04.19.
//

#include "DeleteCommand.h"

void DeleteCommand::execute() {
    std::mutex mx_;
    std::lock_guard<std::mutex> lock(mx_);
    ERRORS errors;
    pTable->Delete(this->key, errors);
    if (errors == ERRORS::SUCCESS){
        std::string s = "Успешно удалено";
        client_socket->send(s);
    } else
        throw InvalidHeadLineException();
}

std::string DeleteCommand::toStr() {
    ERRORS errors;
    std::string answer = "Del " + pTable->Get(this->key, errors);
    return answer;
}