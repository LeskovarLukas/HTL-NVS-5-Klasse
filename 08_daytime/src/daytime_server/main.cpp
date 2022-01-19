#include <iostream>
#include <chrono>
#include "spdlog/spdlog.h"
#include "asio/asio.hpp"
#include "CLI11.hpp"

#include "../include/timeutils.h"


int main(int argc, char const *argv[]) {
    CLI::App app{"daytime_server"};

    unsigned int port = 1113;
    app.add_option("-p, --port", port, "server port");

    CLI11_PARSE(app, argc, argv);


    asio::io_context io_context;
    asio::ip::tcp::endpoint endpoint(asio::ip::tcp::v4(), port);
    asio::ip::tcp::acceptor acceptor(io_context, endpoint);

    asio::ip::tcp::socket socket(io_context);
    acceptor.listen();

    while (true) {
        acceptor.accept(socket);
        asio::ip::tcp::iostream stream{std::move(socket)};
        if (stream) {
            stream << std::chrono::system_clock::now() << std::endl;
        } else {
            spdlog::error("Client connection failed!");
        }
        stream.close();
    }

    acceptor.listen();    
}