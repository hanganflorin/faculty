//
// Created by Florin Hangan on 22/10/2018.
//

#include "Bank.h"

Bank::Bank(int _NumberAccounts, int _NumberThreads, int _TransactionsPerThread) : NumberAccounts(_NumberAccounts), NumberThreads(_NumberThreads), TransactionsPerThread(_TransactionsPerThread) {
    for (int i = 0; i < NumberAccounts; ++i)
        accounts.emplace_back(generateRange(10, 1000) * 1000, i);
}

void Bank::run() {
    for (int i1 = 0; i1 < TransactionsPerThread; ++i1) {
        for (int i = 0; i < NumberThreads; ++i)
            threads.emplace_back(&Bank::Executor, this, i);

        for (auto& i : threads)
            i.join();
        threads.clear();
        checkCorrupted();
    }
}

void Bank::checkCorrupted() {
    for (auto& i : accounts) {
        assert(!i.corrupted());
    }
}

void Bank::Executor(int id) {
    int to = generateRange(1, NumberAccounts-1);
    int from = generateRange(0, to-1);
    int amount = generateRange(1, 5) * 10;
    Transaction transaction(from, to, amount);
    makeTransaction(transaction);
}

void Bank::makeTransaction(Transaction transaction) {

    accounts[transaction.getFrom()].recordSend(transaction);
    accounts[transaction.getTo()].recordReceive(transaction);

}