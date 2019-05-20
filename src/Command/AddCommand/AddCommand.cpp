//
// Created by dmitry on 14.04.19.
//

#include "AddCommand.h"

void AddCommand::execute() {
    std::lock_guard<std::recursive_mutex> lock(_mx);
    ERRORS errors;
    pTable->Add(this->key, this->exptime, this->length, this->value, errors);
    if (errors == ERRORS::SUCCESS) {
        // Вызвать setTimer Cachmanager
        std::string s = "Добавление успешно!";
        client_socket->send(s);
    } else
        throw InvalidHeadLineException();
    //выполнение команды
    //тут может быть проверка на время жизни ключа => отправка запроса
    //на CacheManager для установки timer
    //и прочие команды
}


std::string AddCommand::toStr() {
    std::string answer =
            "Add " + this->key + " " + std::to_string(this->exptime) + " " + std::to_string(this->length) + " " +
            (char *) this->value;
    return answer;
}

void AddCommand::setValue(std::byte *value) {
    this->value = value;
}