//
// Created by Florin Hangan on 18/01/2019.
//

#include "utils.h"
#include <iostream>
#include <random>

int generateRange(int x, int y) {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uid(x, y);
    return uid(rng);
}