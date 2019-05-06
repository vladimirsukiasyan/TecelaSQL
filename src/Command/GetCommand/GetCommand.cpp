//
// Created by vladimir on 14.04.19.
//

#include "GetCommand.h"

void GetCommand::execute() {
    std::mutex mx_;
    std::lock_guard<std::mutex> lock(mx_);
    std::string answer = pTable->Get(this->key);
    if (answer == "error")
        throw InvalidTextLineException();
    else
        client_socket->send(answer);
}