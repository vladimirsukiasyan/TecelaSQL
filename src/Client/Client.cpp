#include <utility>

//
// Created by vladimir on 26.05.19.
//

#include "Client.h"

void Client::handle_request() {
    auto headlineCallback = getCallbackFunction(&Client::handle_headline);

//    Received head line
    _client_socket->async_recv(headlineCallback);

}

void Client::handle_headline(const boost::system::error_code &error, size_t bytes_transferred) {
    // Getting received data from client_socket
    std::string request = std::string(_client_socket->_readBuf,bytes_transferred);

    try {
        _query->parseHeadLine(request);
    }
    catch (InvalidHeadLineException &exception) {
        _client_socket->async_send(exception.what());

        auto headlineCallback = getCallbackFunction(&Client::handle_headline);

        //Received head line
        _client_socket->async_recv(headlineCallback);
        return;
    }

    if(_query->get_method()==METHOD::DISCONNECT){
        disconnectCallback();
        return;
    }

    if (!_query->hasToSendValueLine()) {
        try {
            std::string response=_query->getCommand()->execute();
            _client_socket->async_send(response);
            //TODO тут мы принимаем ответ и отправляем его юзверу
            //TODO не забыть про connected=false, когда мы выполняем DISCONNECTED COMMAND
        }
        catch (NotFoundKeyException &exception) {
            _client_socket->async_send(exception.what());
        }
        catch (NotEnoughMemoryException &exception){
            _client_socket->async_send(exception.what());
        }
        // After sending response to user
        // we must wait the next request from him
        handle_request();

    } else {
        // Sending response(but empty in this case), which is being waiting by client,
        // in order to client can enter the request
        _client_socket->async_send("OK");

        //Wait value line from client
        auto valuelineCallback = getCallbackFunction(&Client::handle_valueline);
        _client_socket->async_recv(valuelineCallback);
    }
}

void Client::handle_valueline(const boost::system::error_code &error, size_t bytes_transferred) {
    // Received value line
    std::string request = std::string(_client_socket->_readBuf,bytes_transferred);

    _query->setCommandValue(request);
    try {
        std::string response=_query->getCommand()->execute();
        _client_socket->async_send(response);
    }
    catch (NotFoundKeyException &exception) {
        _client_socket->async_send(exception.what());
    }
    catch (NotEnoughMemoryException &exception){
        _client_socket->async_send(exception.what());
    }
    // wait the next request from client
    handle_request();

}

void Client::handle_response(const boost::system::error_code &, size_t) {
    //CALLBACK ON SEND SOMETHING TO CLIENT
}

Socket::callback_function Client::getCallbackFunction(void(Client::*pFunction)(const boost::system::error_code &error, size_t bytes_transferred)){
    return boost::bind(
            pFunction,
            this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred
    );
}

void Client::setDisconnectCallback(std::function<void()> disconnectCallback) {
    this->disconnectCallback= std::move(disconnectCallback);
}