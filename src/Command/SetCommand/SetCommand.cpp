//
// Created by vladimir on 14.04.19.
//

#include "SetCommand.h"

void SetCommand :: execute(){
    std::mutex mx_;
    std::lock_guard<std::mutex> lock(mx_);
    bool success = pTable->Set(this->key, this->exptime, this->length, this->value);
    if (success){
        std::string s = "Успешно";
        client_socket->send(s);
    }else
        throw InvalidTextLineException();

};