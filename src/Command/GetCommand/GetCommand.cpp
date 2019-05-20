//
// Created by vladimir on 14.04.19.
//

#include "GetCommand.h"

void GetCommand::execute() {
    std::lock_guard<std::recursive_mutex> lock(_mx);
    ERRORS errors;
    std::string answer = pTable->Get(this->key, errors);
    if (errors != ERRORS::SUCCESS) {
        throw InvalidHeadLineException();
    }
    else
        client_socket->send(answer);
}

std::string GetCommand::toStr() {
    ERRORS errors;
    std::string answer = "Get " + pTable->Get(this->key, errors);
    return answer;
}