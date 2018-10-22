//
// Created by Florin Hangan on 22/10/2018.
//

#ifndef LAB1_BANK_H
#define LAB1_BANK_H

#include <thread>
#include <vector>
#include <cassert>
#include "Account.h"
#include "utils.h"

class Bank {
private:
    std::vector<Account> accounts;
    std::vector<std::thread> threads;
    const int NumberAccounts = 100;
    const int NumberThreads = 200;
    const int TransactionsPerThread = 100;
public:

    Bank(int, int, int);
    void run();
    void checkCorrupted();
    void Executor(int);
    void makeTransaction(Transaction);
};

#endif //LAB1_BANK_H
