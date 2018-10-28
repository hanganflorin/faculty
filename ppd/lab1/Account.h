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
    std::vector <Transaction> sentTransactions;
    std::vector <Transaction> receiveTransactions;
    std::mutex* account_mutex;

public:
    explicit Account(int _balance = 0, int _id = 0);
    void RecordSend(Transaction);
    void RecordReceive(Transaction);

    bool IsCorrupted();
};


#endif //LAB1_ACCOUNT_H
