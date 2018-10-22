//
// Created by Florin Hangan on 22/10/2018.
//

#ifndef LAB1_ACCOUNT_H
#define LAB1_ACCOUNT_H

#include <vector>
#include <mutex>
#include "Transaction.h"

class Account {
private:
    int id;
    long long balance;
    const long long initialBalance;
    std::vector <Transaction> Transactions;
    std::vector <Transaction> receiveTransactions;
    std::mutex* account_mutex;

public:
    explicit Account(int _balance = 0, int _id = 0);
    void recordSend(Transaction);
    void recordReceive(Transaction);

    bool corrupted();
    const std::vector<Transaction> &getTransactions() const;
    const std::vector<Transaction> &getReceiveTransactions() const;
    const long long int getInitialBalance() const;
    long long getBalance() const;
};


#endif //LAB1_ACCOUNT_H
