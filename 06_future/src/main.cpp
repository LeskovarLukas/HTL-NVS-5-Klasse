#include <iostream>
#include <future>
#include <thread>

#include "calc_factors.h"
#include "CLI11.hpp"


std::string checkNumber(const std::string&);

void printFactors(const std::vector<InfInt>&, const std::vector<InfInt>&);

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

    while (!factorFutures.empty()) {
        auto factorFuture = factorFutures.begin();
        
        if (factorFuture->wait_for(std::chrono::milliseconds(1000)) == std::future_status::ready) {
            std::vector<InfInt> factors = factorFuture->get();

            std::thread t{printFactors, std::ref(factors), std::ref(numbers)};

            t.join();
            factorFutures.erase(factorFuture);
            numbers.erase(numbers.begin());
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

void printFactors(const std::vector<InfInt>& factors, const std::vector<InfInt>& numbers) {
    std::cout << numbers[0] << ": ";
    for (const InfInt& factor : factors) {
        std::cout << factor << " ";
    }
    std::cout << std::endl;
}