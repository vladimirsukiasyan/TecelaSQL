#include <boost/asio/io_service.hpp>
#include <boost/asio/steady_timer.hpp>
#include <chrono>
#include <thread>
#include <iostream>
#include "Server/Server.h"

using namespace boost::asio;

int main()
{
    Server().start();
    return 0;
}