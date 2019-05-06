//
// Created by vladimir on 07.04.19.
//

#include "ClientConnection.h"

std::string ClientConnection::recv() {
    if (_sock.available())
        _already_read += _sock.read_some(
                boost::asio::buffer(_buff + _already_read, max_msg - _already_read));
}

void ClientConnection::send(const std::string &response) {
    _sock.write_some(boost::asio::buffer(response));
}

void ClientConnection::client_session() {
    while(true){
        recv();
        //WORK WITH CLIENT COMMAND
        try{
            bool found_enter = std::find(_buff, _buff + _already_read, '\n') < _buff + _already_read;
            if ( !found_enter)
                return; // message is not full
            // process the msg
            size_t pos = std::find(_buff, _buff + _already_read, '\n') - _buff;
            std::string msg(_buff, pos);
//            app->requestHandler(msg);
        }
        catch(InvalidTextLineException &e){
            send("ERROR: Invalid command!");
        }
    }
}



