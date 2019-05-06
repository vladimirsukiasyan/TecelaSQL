
#include "Query.h"

Command *Query::getCommand() {
    return command;
}

void Query::parseHeadLine(const std::string &headBuffer) {
    //парсинг первой части запроса
    //<command_string><key><exptime><length>
    std::vector<std::string> tokens;
    boost::split(tokens, headBuffer,boost::is_any_of(" "));

    if (tokens.empty()){
        throw InvalidTextLineException();
    }
    std::string command_string=tokens[0];
    boost::to_lower(command_string);

    if(command_string=="get"){
        method=METHOD::GET;
    }
    else if(command_string == "add") {
        method=METHOD::ADD;

        if(tokens.size()!=ADD_COMMAND_HEADLINE_PARAMS_COUNT){
            throw InvalidTextLineException();
        }

        std::string::size_type sz1=0,sz2 = 0;
        long long exptime;
        long long length;
        try{
            exptime=std::stoll(tokens[2],&sz1);
            length=std::stoll(tokens[3],&sz2);
        }
        catch (std::invalid_argument &e){
            throw InvalidTextLineException();
        }
        if(sz1!=tokens[2].size() || sz2!=tokens[3].size())
            throw InvalidTextLineException();

        command=new AddCommand(tokens[0],exptime,length,);
        return;
    }
    else if (command_string == "set") {
        method=METHOD::SET;
    }
    else if (command_string == "delete") {
        method=METHOD::DELETE;
    }
    else if (command_string == "touch"){
        method=METHOD::TOUCH;
    }
    else if (command_string == "incr"){
        method=METHOD::INCR;
    }
    else if (command_string == "decr"){
        method=METHOD::DECR;
    }
    else if (command_string=="flush_all"){
        method=METHOD::FLUSH_ALL;
    }
    else if(command_string=="disconnect"){
        method=METHOD::DISCONNECT;
    }
    else throw InvalidTextLineException();

}

bool Query::hasToSendBodyLine() {
    return  method==METHOD::ADD ||method==METHOD ::SET;
}

void Query::setCommandValue(const std::string bodyBuffer) {
    if(method==METHOD::ADD){
        ((AddCommand*)command)->setValue((std::byte *) bodyBuffer.c_str());
    }
//    if(method==METHOD::SET){
//        ((SetCommand*)command)->setValue((std::byte *) bodyBuffer.c_str());
//    }
}