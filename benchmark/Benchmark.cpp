#include "Benchmark.h"

void ServerBenchmark::connect(const ip::tcp::endpoint &ep) {
    sock_.connect(ep);
}

void ServerBenchmark::loop() {
    write();
    auto start = std::chrono::system_clock::now();
    for (int i = 0; i < 100000; ++i) {
        get_request();
        read_answer();
    }
    auto end = std::chrono::system_clock::now();
    auto elapsed = end - start;
    float rpm = elapsed.count() / 100000;
    std::cout << std::setprecision(16) << rpm << " - запросов в секунду" << std::endl;
    del_request();
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

void ServerBenchmark::write() {
    std::string query;
    query = "add 12 100 10";
    sock_.write_some(buffer(query));
    query = "0123456789";
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
    boost::asio::thread_pool pool(4);
    for (int i = 0; i < 4; i++)
        boost::asio::post(pool, [=] { run_client(); });
    pool.join();
    return 0;
};