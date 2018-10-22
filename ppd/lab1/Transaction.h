//
// Created by Florin Hangan on 22/10/2018.
//

#ifndef LAB1_TRANSACTION_H
#define LAB1_TRANSACTION_H

class Transaction{
private:
    static int auto_id;
private:
    const int id;
    int from, to;
    int amount;
public:
    Transaction(int, int, int);
    int getFrom() const;
    int getTo() const;
    int getAmount() const;
    const int getId() const;
    static int getAuto_id();
};

#endif //LAB1_TRANSACTION_H
