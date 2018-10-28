//
// Created by Florin Hangan on 22/10/2018.
//

#include "Transaction.h"

int Transaction::auto_id = 0;

Transaction::Transaction(int _from, int _to, int _amount) : from(_from), to(_to), id(auto_id++), amount(_amount) {}

int Transaction::getFrom() const {
    return from;
}

int Transaction::getTo() const {
    return to;
}

int Transaction::getAmount() const {
    return amount;
}
