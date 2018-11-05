#include "utils.h"
#include "Matrix.h"
#include <chrono>
#include <iostream>

int main() {
    std::cout << "Reading M1...\n";
    Matrix matrix1("M1000_1.txt");
    std::cout << "Reading M2...\n";
    Matrix matrix2("M1000_2.txt");

//    std::cout << "Reading M1...\n";
//    Matrix matrix1("matrix1.in");
//    std::cout << "Reading M2...\n";
//    Matrix matrix2("matrix2.in");

    std::cout << "Start computing...\n";
    auto start = std::chrono::high_resolution_clock::now();
    Matrix res = matrix1 * matrix2;
    auto finish = std::chrono::high_resolution_clock::now();

    //res.Print();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Elapsed time: " << elapsed.count() << '\n';
    return 0;
}