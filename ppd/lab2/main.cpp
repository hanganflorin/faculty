#include "utils.h"
#include "Matrix.h"
#include <chrono>
#include <iostream>

int main() {
    std::cout << "Reading M1...\n";
    Matrix matrix1("M10000_1.txt");
    std::cout << "Reading M2...\n";
    Matrix matrix2("M10000_2.txt");
//    int N = 10000;
//    Matrix matrix1(N, N);
//    Matrix matrix2(N, N);
//    matrix1.Randomize(1000, 10000);
//    matrix2.Randomize(1000, 10000);
//    matrix1.PrintToFile("M10000_1.txt");
//    matrix1.PrintToFile("M10000_2.txt");
    //matrix2.Print();
    std::cout << "Start computing...\n";
    auto start = std::chrono::high_resolution_clock::now();
    Matrix res = matrix1 + matrix2;
    auto finish = std::chrono::high_resolution_clock::now();

    //res.Print();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Elapsed time: " << elapsed.count() << '\n';
    return 0;
}