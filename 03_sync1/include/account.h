//
// Created by Lukas Leskovar on 18.10.21.
//

#ifndef INC_03_SYNC1_ACCOUNT_H
#define INC_03_SYNC1_ACCOUNT_H


class Account {
private:
    int balance{};
    std::mutex withdrawMutex{};

public:
    int getBalance();
    void deposit(int);
    bool withdraw(int);
};


#endif //INC_03_SYNC1_ACCOUNT_H
