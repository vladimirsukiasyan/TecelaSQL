//
// Created by vladimir on 13.04.19.
//
#include "Application.h"

void Application::requestHandler(const std::string &buffer) {
    // TODO send REQUEST_HEADER
    //   socket->send(REQUEST_HEADER);

    //парсинг запроса
    //получение нужной команды(Command) с необходимыми параметрами
    //выполнение команды

    if(query->isHeadLineReceived){
        assert(!command);
        query->setCommandValue(buffer);
        query->isHeadLineReceived= false;
    }
    else{
        query->parseHeadLine(buffer);

        query->isHeadLineReceived= true;

        if(query->hasToSendBodyLine()){
            return;
        }
    }

    query->getCommand()->execute();
}

#include "Application.h"
