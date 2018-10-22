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

const int NumberAccounts = 10;
const int NumberThreads = 200;
const int TransactionsPerThread = 100;


int main() {
    Bank bank(NumberAccounts, NumberThreads, TransactionsPerThread);
    bank.run();
    return 0;
}