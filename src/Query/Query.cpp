//
// Created by vladimir on 13.04.19.
//

#include "Query.h"

Command *Query::getCommand() {
    return command;
}


//Parse first line(HEAD LINE) from client

void Query::parseHeadLine(const std::string &headBuffer) {
    //парсинг первой части запроса
    //<command_string><key><exptime><length>
    std::vector<std::string> tokens;
    boost::split(tokens, headBuffer, boost::is_any_of(" "));

    if (tokens.empty()) {
        throw InvalidHeadLineException();
    }
    std::string command_string = tokens[0];
    boost::to_lower(command_string);

    if (command_string == "get") {
        method = METHOD::GET;

        if (tokens.size() != GET_COMMAND_HEADLINE_PARAMS_COUNT) {
            throw InvalidHeadLineException();
        }

        command = new GetCommand(tokens[1], client_socket);
    }
    else if (command_string == "add") {
        method = METHOD::ADD;

        if (tokens.size() != ADD_COMMAND_HEADLINE_PARAMS_COUNT) {
            throw InvalidHeadLineException();
        }

        std::string::size_type sz1 = 0, sz2 = 0;
        long long exptime;
        long long length;
        try {
            exptime = std::stoll(tokens[2], &sz1);
            length = std::stoll(tokens[3], &sz2);
        }
        catch (std::invalid_argument &e) {
            throw InvalidHeadLineException();
        }
        if (sz1 != tokens[2].size() || sz2 != tokens[3].size())
            throw InvalidHeadLineException();

        command = new AddCommand(tokens[1], exptime, length, client_socket);
        return;
    }

    else if (command_string == "set") {
        method = METHOD::SET;

        if (tokens.size() != SET_COMMAND_HEADLINE_PARAMS_COUNT) {
            throw InvalidHeadLineException();
        }

        std::string::size_type sz1 = 0, sz2 = 0;
        long long exptime;
        long long length;
        try {
            exptime = std::stoll(tokens[2], &sz1);
            length = std::stoll(tokens[3], &sz2);
        }
        catch (std::invalid_argument &e) {
            throw InvalidHeadLineException();
        }
        if (sz1 != tokens[2].size() || sz2 != tokens[3].size())
            throw InvalidHeadLineException();

        command = new SetCommand(tokens[1], exptime, length, client_socket);
        return;
    }

    else if (command_string == "delete") {

        method = METHOD::DELETE;
        if(tokens.size()!=DELETE_COMMAND_HEADLINE_PARAMS_COUNT){
            throw InvalidHeadLineException();
        }

        command=new DeleteCommand(tokens[1],client_socket);

    }

    else if (command_string == "touch") {
        method = METHOD::TOUCH;
    }

    else if (command_string == "incr") {
        method = METHOD::INCR;
    }

    else if (command_string == "decr") {
        method = METHOD::DECR;
    }

    else if (command_string == "flush_all") {
        method = METHOD::FLUSH_ALL;
    }

    else if (command_string == "disconnect") {
        method = METHOD::DISCONNECT;

       // command=new DisconnetCommand(client_socket);
    }

    else throw InvalidHeadLineException();

}

// If client sent ADD or SET command, server has to receive one more line
bool Query::hasToSendValueLine() {
    return method == METHOD::ADD || method == METHOD::SET;
}

void Query::setCommandValue(const std::string &valueBuffer) {
    if (method == METHOD::ADD) {
        ((AddCommand *) command)->setValue((std::byte *) valueBuffer.c_str());
    }
    if (method == METHOD::SET) {
        ((SetCommand *) command)->setValue((std::byte *) valueBuffer.c_str());
    }
}

Query::Query(const Socket::ptr &socket) :
        client_socket(Socket::ptr(socket)){
}

Query::~Query() {
    delete command;
}

