//
// Created by Florin Hangan on 22/10/2018.
//

#include "Account.h"

long long Account::getBalance() const {
    return balance;
}

Account::Account(int _balance, int _id) : balance(_balance), initialBalance(_balance), id(_id) {
    this->account_mutex = new std::mutex;
}

const long long int Account::getInitialBalance() const {
    return initialBalance;
}

void Account::recordSend(Transaction transaction){
    this->account_mutex->lock();
    Transactions.push_back(transaction);
    this->balance -= transaction.getAmount();
    this->account_mutex->unlock();
}

void Account::recordReceive(Transaction transaction) {
    this->account_mutex->lock();
    receiveTransactions.push_back(transaction);
    this->balance += transaction.getAmount();
    this->account_mutex->unlock();
}

const std::vector<Transaction> &Account::getTransactions() const {
    return Transactions;
}

const std::vector<Transaction> &Account::getReceiveTransactions() const {
    return receiveTransactions;
}

bool Account::corrupted() {
    long long computed_balance = this->initialBalance;
    for (const auto& i : Transactions)
        computed_balance -= i.getAmount();
    for (const auto& i : receiveTransactions)
        computed_balance += i.getAmount();
    return !computed_balance == balance;
}