//
// Created by vladimir on 14.04.19.
//

#include "GetCommand.h"

void GetCommand::execute() {
    std::lock_guard<std::recursive_mutex> lock(_mx);

    std::string &answer;
    if (pTable->Get(this->key, answer) == ERRORS::SUCCESS)
        throw InvalidHeadLineException();
    else
        client_socket->send(answer);
}

std::string GetCommand::toStr() {
    std::string answer = "Get " + pTable->Get(this->key);
    return answer;
}