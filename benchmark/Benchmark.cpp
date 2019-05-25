#include "Benchmark.h"

void ServerBenchmark::connect(const ip::tcp::endpoint &ep) {
    sock_.connect(ep);
}

void ServerBenchmark::loop() {
    auto start = std::chrono::system_clock::now();
    for (int i = 0; i < 100000; ++i) {
        get_request();
        read_answer();
    }
    auto end = std::chrono::system_clock::now();
    auto elapsed = end - start;
    float rps = elapsed.count() / 100000;
    std::cout << std::setprecision(16) << rps << " - запросов в секунду" << std::endl;
}

void ServerBenchmark::get_request() {
    std::string query;
    query = "get 12";
    sock_.write_some(buffer(query));
}

void ServerBenchmark::del_request() {
    std::string query;
    query = "del 12";
    sock_.write_some(buffer(query));
}

void ServerBenchmark::read_answer() {
    size_t bytes_transferred = sock_.read_some(buffer(buff_));
    std::string response(buff_, bytes_transferred);
    //std::cout << response << std::endl;
}

void ServerBenchmark::write_command() {
    std::string query;
    query = "add 12 100 5";
    sock_.write_some(buffer(query));
}

void ServerBenchmark::write_value() {
    std::string query;
    query = "value";
    sock_.write_some(buffer(query));
}

void run_client() {
    ServerBenchmark client;
    try {
        client.connect(ep);
        client.loop();
    }
    catch (boost::system::system_error &err) {
        std::cout << "client terminated " << std::endl;
    }
}

int main() {
    ServerBenchmark client;
    client.write_command();
    client.write_value();
    boost::asio::thread_pool pool(4);
    for (int i = 0; i < 4; i++)
        boost::asio::post(pool, [=] { run_client(); });
    pool.join();
    client.del_request();
    return 0;
};