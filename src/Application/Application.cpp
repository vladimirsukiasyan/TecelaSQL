//
// Created by vladimir on 13.04.19.
//
#include "Application.h"

void Application::requestHandler(Socket::ptr client_socket) {
    // TODO send REQUEST_HEADER
    //   socket->send(REQUEST_HEADER);

    //парсинг запроса
    //получение нужной команды(Command) с необходимыми параметрами
    //выполнение команды
    query->setSocket(client_socket);

    while(true){
        if (query->isHeadLineReceived) {
            assert(!command);

            std::string value = client_socket->recv();

            query->setCommandValue(value);

            query->getCommand()->execute();

            query->isHeadLineReceived = false;

        } else {
            std::string headline = client_socket->recv();

            query->parseHeadLine(headline);

            query->isHeadLineReceived = true;

            if (!query->hasToSendBodyLine()) {
                query->getCommand()->execute();
            }
        }
    }
}
