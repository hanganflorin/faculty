//
// Created by Florin Hangan on 22/10/2018.
//

#include <iostream>
#include "Account.h"

Account::Account(int _balance, int _id) : balance(_balance), initialBalance(_balance), id(_id) {
    this->account_mutex = new std::mutex;
}

void Account::RecordSend(Transaction transaction){
    this->account_mutex->lock();
    sentTransactions.push_back(transaction);
    this->balance -= transaction.getAmount();
    this->account_mutex->unlock();
}

void Account::RecordReceive(Transaction transaction) {
    this->account_mutex->lock();
    receiveTransactions.push_back(transaction);
    this->balance += transaction.getAmount();
    this->account_mutex->unlock();
}

bool Account::IsCorrupted() {
    this->account_mutex->lock();
    long long computed_balance = this->initialBalance;
    for (const auto& i : sentTransactions)
        computed_balance -= i.getAmount();
    for (const auto& i : receiveTransactions)
        computed_balance += i.getAmount();
    bool result = computed_balance != balance;
    this->account_mutex->unlock();
    return result;
}