//
// Created by vladimir on 13.04.19.
//
#include "Application.h"

void Application::handle_client() {
    auto headlineCallback = getCallbackFunction(&Application::handle_headline);

    //Received head line
    _client_socket->recv(headlineCallback);
}

void Application::handle_headline(const boost::system::error_code &error, size_t bytes_transferred) {
    // Getting received data from client_socket
    std::string request = std::string(_client_socket->_readBuf,bytes_transferred);

    try {
        _query->parseHeadLine(request);
    }
    catch (InvalidHeadLineException &exception) {
        _client_socket->send(exception.what());

        auto headlineCallback = getCallbackFunction(&Application::handle_headline);

        //Received head line
        _client_socket->recv(headlineCallback);
        return;
    }

    if (!_query->hasToSendValueLine()) {
        try {
            _query->getCommand()->execute();
        }
        catch (InvalidHeadLineException &exception) {
            // INVALID TEXTLINE
            _client_socket->send(exception.what());
        }
        // After sending response to user
        // we must wait the next request from him
        auto headlineCallback = getCallbackFunction(&Application::handle_headline);

        //Received head line
        _client_socket->recv(headlineCallback);

    } else {
        // Sending response(but empty in this case), which is being waiting by client,
        // in order to client can enter the request
        _client_socket->send("OK");

        //Wait value line from client
        auto valuelineCallback = getCallbackFunction(&Application::handle_valueline);
        _client_socket->recv(valuelineCallback);
    }
}

void Application::handle_valueline(const boost::system::error_code &error, size_t bytes_transferred) {
    // Received value line
    std::string request = std::string(_client_socket->_readBuf,bytes_transferred);

    _query->setCommandValue(request);
    try {
        _query->getCommand()->execute();
    }
    catch (std::exception &exception){
        _client_socket->send(exception.what());
    }
    handle_client();

}

void Application::handle_response(const boost::system::error_code &, size_t) {
    //CALLBACK ON SEND SOMETHING TO CLIENT
}


Socket::callback_function Application::getCallbackFunction(void(Application::*pFunction)(const boost::system::error_code &error, size_t bytes_transferred)){
    return boost::bind(
            pFunction,
            this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred
    );
}

