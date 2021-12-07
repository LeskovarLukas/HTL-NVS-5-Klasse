#include <iostream>

#include "calc_factors.h"
#include "CLI11.hpp"


std::string checkNumber(const std::string&);

int main(int argc, char const *argv[]){
    CLI::App app("Factor numbers");
    std::vector<std::string> numbersInput;
    std::vector<InfInt> numbers;

    app.add_option("number", numbersInput, "numbers to factor")->required()->check(checkNumber);
    CLI11_PARSE(app, argc, argv);

    for (const std::string& number : numbersInput) {
        numbers.push_back(InfInt(number));
    }

    for (const InfInt& number : numbers) {
        std::vector<InfInt> factors = get_factors(number);

        std::cout << number << ": ";
        for (const InfInt& factor : factors) {
            std::cout << factor << " ";
        }
        std::cout << std::endl;
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