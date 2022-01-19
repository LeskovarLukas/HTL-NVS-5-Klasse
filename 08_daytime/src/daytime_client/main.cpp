#include <iostream>
#include <chrono>
#include "spdlog/spdlog.h"
#include "asio/asio.hpp"
#include "CLI11.hpp"

int main(int argc, char const *argv[]) {
    
    // Sink with color
    // auto console = spdlog::stdout_color_mt("console");	
    // auto console_sink = dynamic_cast<spdlog::sinks::stdout_color_sink_mt *>(console->sinks().back().get());
    // console_sink->set_color(spdlog::level::info, console_sink->red);
    // console->info("Hello, world!");
    // spdlog::info("Hello, world!");
    // spdlog::warn("Client is running");
    // spdlog::error("Client is running away");
    // spdlog::critical("Client is gone");

    CLI::App app{"daytime_client"};

    unsigned int port = 1113;
    app.add_option("--port", port, "port to connect to");

    CLI11_PARSE(app, argc, argv);


    spdlog::set_level(spdlog::level::debug);

    spdlog::debug("Atempting connection...");
    asio::ip::tcp::iostream stream{"localhost", std::to_string(port)};
    stream.expires_after(std::chrono::seconds(5));

    if (stream) {
        spdlog::debug("Connected");
        stream << "" << std::endl;

        if (stream) {
            spdlog::debug("Received response");
            std::string line;
            std::getline(stream, line);
            std::cout << line << std::endl;
        } else {
            spdlog::error(stream.error().message());
        }
    }
    else {
        spdlog::error("Could not connect to server");
    }
    stream.close();

    return 0;
}