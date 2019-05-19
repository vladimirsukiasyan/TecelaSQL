//
// Created by vladimir on 14.04.19.
//

#include "DeleteCommand.h"

void DeleteCommand::execute() {
    std::mutex mx_;
    std::lock_guard<std::mutex> lock(mx_);
    bool success = pTable->Delete(this->key);
    if (success) {
        std::string s = "Успешно удалено";
        client_socket->send(s);
    } else
        throw InvalidHeadLineException();
}

std::string DeleteCommand::toStr() {
    std::string answer = "Del " + pTable->Get(this->key);
    return answer;
}