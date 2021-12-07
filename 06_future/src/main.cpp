#include <iostream>
#include <future>

#include "calc_factors.h"
#include "CLI11.hpp"


std::string checkNumber(const std::string&);

int main(int argc, char const *argv[]){
    CLI::App app("Factor numbers");
    std::vector<std::string> numbersInput;
    std::vector<InfInt> numbers; 
    std::vector<std::future<std::vector<InfInt>> > factorFutures{};

    app.add_option("number", numbersInput, "numbers to factor")->required()->check(checkNumber);
    CLI11_PARSE(app, argc, argv);

    for (const std::string& number : numbersInput) {
        numbers.push_back(InfInt(number));
    }

    for (const InfInt& number : numbers) {
        factorFutures.push_back(std::async(std::launch::async, get_factors, number));
    }

    int index = 0;  // does not feel right;
    while (!factorFutures.empty()) {
        auto factorFuture = factorFutures.begin();
        
        if (factorFuture->wait_for(std::chrono::milliseconds(1000)) == std::future_status::ready) {
            std::vector<InfInt> factors = factorFuture->get();

            std::cout << numbers[index++] << ": ";
            for (const InfInt& factor : factors) {
                std::cout << factor << " ";
            }
            std::cout << std::endl;
            factorFutures.erase(factorFuture);
        }
    }

    return 0;
}



std::string checkNumber(const std::string& number) {
    if (number.empty()) {
        return "Number cannot be empty";
    } 
    else if (number[0] == '-') {
        return "Number should be positive";
    }
    else if (number.find_first_not_of("0123456789") != std::string::npos) {
        return std::string(number) + " contains non-numeric characters";
    }
    return "";
}