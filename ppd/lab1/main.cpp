#include <iostream>
#include <random>
#include <vector>
#include <thread>
#include <mutex>
#include <cassert>
#include "Account.h"
#include "Transaction.h"
#include "utils.h"
#include "Bank.h"

const int NumberAccounts = 100;
const int NumberThreads = 200;
const int TransactionsPerThread = 100;


int main() {
    Bank bank(NumberAccounts, NumberThreads, TransactionsPerThread);
    auto start = std::chrono::high_resolution_clock::now();
    bank.run();
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Time: " << elapsed.count() << " s\n";
    return 0;
}