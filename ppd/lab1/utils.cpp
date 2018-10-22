//
// Created by Florin Hangan on 22/10/2018.
//


#include <iostream>
#include <random>

int generateRange(int x, int y) {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uid(x, y);
    return uid(rng);
}
