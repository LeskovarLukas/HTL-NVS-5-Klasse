#include <iostream>
#include <future>
#include <thread>

#include "calc_factors.h"
#include "CLI11.hpp"


std::string checkNumber(const std::string&);

void printFactors(std::vector<std::shared_future<std::vector<InfInt>> >&, std::vector<InfInt>&);

void checkFactors(std::vector<std::shared_future<std::vector<InfInt>> >&, std::vector<InfInt>&);


int main(int argc, char const *argv[]){
    CLI::App app("Factor numbers");
    std::vector<std::string> numbersInput;
    std::vector<InfInt> numbers; 
    std::vector<std::shared_future<std::vector<InfInt>> > factorFutures;

    bool useAsync = false;
    app.add_flag("-a, --async", useAsync, "Use async");
    app.add_option("number", numbersInput, "numbers to factor")->required()->check(checkNumber);
    CLI11_PARSE(app, argc, argv);
    

    for (const std::string& number : numbersInput) {
        numbers.push_back(InfInt(number));
    }

    auto start = std::chrono::system_clock::now();

    for (const InfInt& number : numbers) {
        if (useAsync) {
            factorFutures.push_back(std::async(std::launch::async, get_factors, number));
        } else {
            factorFutures.push_back(std::async(std::launch::deferred, get_factors, number));
            factorFutures.back().wait();
        }
    }

    std::thread printThread{printFactors, std::ref(factorFutures), std::ref(numbers)};
    std::thread checkThread{checkFactors, std::ref(factorFutures), std::ref(numbers)};

    unsigned int i = 0;
    while (i < factorFutures.size()) {
        if (factorFutures[i].wait_for(std::chrono::milliseconds(100)) == std::future_status::ready) {
            i++;
        }
    }
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start);

    printThread.join();
    checkThread.join();

    std::cout << "Time elapsed used for factoring: " << duration.count() << "ms" << std::endl;

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

void printFactors(std::vector<std::shared_future<std::vector<InfInt>> >& factorFutures, std::vector<InfInt>& numbers) {
    unsigned int i = 0;
    while (i < factorFutures.size()) {
        auto& factorFuture = factorFutures.at(i);

        if (factorFuture.wait_for(std::chrono::milliseconds(1000)) == std::future_status::ready) {
            std::vector<InfInt> factors = factorFuture.get();

            std::cout << numbers[i] << ": ";
            for (const InfInt& factor : factors) {
                std::cout << factor << " ";
            }
            std::cout << std::endl;
            i++;
        }
    }
}

void checkFactors(std::vector<std::shared_future<std::vector<InfInt>> >& factorFutures, std::vector<InfInt>& numbers) {
    unsigned int i = 0;
    while (i < factorFutures.size()) {
        auto& factorFuture = factorFutures.at(i);

        if (factorFuture.wait_for(std::chrono::milliseconds(1000)) == std::future_status::ready) {
            std::vector<InfInt> factors = factorFuture.get();
            InfInt checkSum = 1;

            for (const InfInt& factor : factors) {
                checkSum *= factor;
            }
            
            if (checkSum != numbers[i]) {
                std::cerr << "ERROR: " << numbers[i] << " is not the product of its factors" << std::endl;
            }

            i++;
        }
    }
}
