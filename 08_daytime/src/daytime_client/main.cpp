#include <iostream>
#include <chrono>
#include "spdlog/spdlog.h"
#include "asio/asio.hpp"

int main() {
    
    // Sink with color
    // auto console = spdlog::stdout_color_mt("console");	
    // auto console_sink = dynamic_cast<spdlog::sinks::stdout_color_sink_mt *>(console->sinks().back().get());
    // console_sink->set_color(spdlog::level::info, console_sink->red);
    // console->info("Hello, world!");
    // spdlog::info("Hello, world!");
    // spdlog::warn("Client is running");
    // spdlog::error("Client is running away");
    // spdlog::critical("Client is gone");

    spdlog::set_level(spdlog::level::debug);
    asio::ip::tcp::iostream stream("localhost", "1113");

    spdlog::debug("Atempting connection...");
    if (stream) {
        std::string line;
        std::getline(stream, line);
        std::cout << line << std::endl;
    }
    else {
        spdlog::error("Could not connect to server");
    }

    return 0;
}