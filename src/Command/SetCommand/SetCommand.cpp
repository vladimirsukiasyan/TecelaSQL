//
// Created by vladimir on 14.04.19.
//

#include "SetCommand.h"

void SetCommand::execute() {
    std::mutex mx_;
    std::lock_guard<std::recursive_mutex> lock(_mx);
    if (pTable->Set(this->key, this->exptime, this->length, this->value) == ERRORS::SUCCESS) {
        std::string s = "Успешно";
        client_socket->send(s);
    } else
        throw InvalidHeadLineException();

};

std::string SetCommand::toStr() {
    std::string answer =
            "Set " + this->key + " " + std::to_string(this->exptime) + " " + std::to_string(this->length) + " " +
            (char *) this->value;
    return answer;
}

void SetCommand::setValue(std::byte *value) {
    this->value = value;
}