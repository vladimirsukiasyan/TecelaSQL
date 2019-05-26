//
// Created by vladimir on 13.04.19.
//

#include "Query.h"

Command *Query::getCommand(){
    switch (_method) {
        case METHOD::GET: {
            return new GetCommand(
                    std::any_cast<std::string>(_params["key"])
                    );

        }
        case METHOD::SET: {
            return new SetCommand(
                    std::any_cast<std::string>(_params["key"]),
                    std::any_cast<long long>(_params["exptime"]),
                    std::any_cast<long long>(_params["length"]),
                    std::any_cast<std::byte*>(_params["value"])
                    );
        }
        case METHOD::ADD:{
            return new AddCommand(
                    std::any_cast<std::string>(_params["key"]),
                    std::any_cast<long long>(_params["exptime"]),
                    std::any_cast<long long>(_params["length"]),
                    std::any_cast<std::byte *>(_params["value"])
            );
        }
        case METHOD::DELETE:{
            return new DeleteCommand(
                    std::any_cast<std::string>(_params["key"])
                    );
        }

        case METHOD::INCR:break;
        case METHOD::DECR:break;
        case METHOD::DISCONNECT:break;
        case METHOD::TOUCH:break;
        case METHOD::FLUSH_ALL:break;
    }
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
        _method = METHOD::GET;

        if (tokens.size() != GET_COMMAND_HEADLINE_PARAMS_COUNT) {
            throw InvalidHeadLineException();
        }
        _params["key"] = tokens[1];

//        command = new GetCommand(tokens[1], _client_socket);
    } else if (command_string == "add") {
        _method = METHOD::ADD;

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


        _params["key"] = tokens[1];
        _params["exptime"] = exptime;
        _params["length"] = length;

//        command = new AddCommand(tokens[1], exptime, length, _client_socket);
        return;
    } else if (command_string == "set") {
        _method = METHOD::SET;

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

        _params["key"] = tokens[1];
        _params["exptime"] = exptime;
        _params["length"] = length;

//        command = new SetCommand(tokens[1], exptime, length, _client_socket);
        return;
    } else if (command_string == "delete") {

        _method = METHOD::DELETE;
        if (tokens.size() != DELETE_COMMAND_HEADLINE_PARAMS_COUNT) {
            throw InvalidHeadLineException();
        }

        _params["key"] = tokens[1];

//        command=new DeleteCommand(tokens[1],_client_socket);

    } else if (command_string == "touch") {
        _method = METHOD::TOUCH;
    } else if (command_string == "incr") {
        _method = METHOD::INCR;
    } else if (command_string == "decr") {
        _method = METHOD::DECR;
    } else if (command_string == "flush_all") {
        _method = METHOD::FLUSH_ALL;
    } else if (command_string == "disconnect") {
        _method = METHOD::DISCONNECT;
    } else throw InvalidHeadLineException();

}

// If client sent ADD or SET command, server has to receive one more line
bool Query::hasToSendValueLine() const {
    return _method == METHOD::ADD || _method == METHOD::SET;
}

void Query::setCommandValue(const std::string &valueBuffer) {
    _params["value"] = (std::byte *) valueBuffer.c_str();
}

METHOD Query::get_method() const {
    return _method;
}

Query::Query(){

}

Query::~Query() {
    delete command;
}

