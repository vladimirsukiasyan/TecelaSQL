//
// Created by dmitry on 14.04.19.
//

#include "AddCommand.h"

void AddCommand::execute() {
    std::mutex mx_;
    std::lock_guard<std::mutex> lock(mx_);
    bool success = pTable->Add(this->key, this->exptime, this->length, this->value);
    if (success) {
        // Вызвать setTimer Cachmanager
        std::string s = "Добавление успешно!";
        client_socket->send(s);
    } else
        throw InvalidTextLineException();
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