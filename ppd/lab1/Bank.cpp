//
// Created by Florin Hangan on 22/10/2018.
//

#include "Bank.h"
#include <iostream>

Bank::Bank(int _NumberAccounts, int _NumberThreads, int _TransactionsPerThread) : NumberAccounts(_NumberAccounts), NumberThreads(_NumberThreads), TransactionsPerThread(_TransactionsPerThread) {
    for (int i = 0; i < NumberAccounts; ++i)
        accounts.emplace_back(generateNumber(10, 1000) * 1000, i);
}

void Bank::run() {
    for (int i = 0; i < TransactionsPerThread; ++i) {
        for (int j = 0; j < NumberThreads; ++j)
            threads.emplace_back(&Bank::Executor, this);

        for (auto& i : threads)
            i.join();
        threads.clear();
        CheckCorrupted();
    }
}

void Bank::CheckCorrupted() {
    for (auto& i : accounts) {
        assert(!i.IsCorrupted());
    }
}

void Bank::Executor() {
    int to = generateNumber(1, NumberAccounts - 1);
    int from = generateNumber(0, to - 1);
    int amount = generateNumber(1, 5) * 10;
    Transaction transaction(from, to, amount);
    MakeTransaction(transaction);
}

void Bank::MakeTransaction(Transaction transaction) {

    accounts[transaction.getFrom()].RecordSend(transaction);
    accounts[transaction.getTo()].RecordReceive(transaction);
//    std::cout << "Transaction from " << transaction.getFrom() << " to " << transaction.getTo() << " amount: " << transaction.getAmount() << "\n";
}