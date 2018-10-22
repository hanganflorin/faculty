//
// Created by Florin Hangan on 22/10/2018.
//

#ifndef LAB2_MATRIX_H
#define LAB2_MATRIX_H


#include <fstream>
#include <vector>
#include <iostream>
#include <queue>
#include <mutex>

class Matrix {
private:
    std::vector<std::vector<long long> > data;
    int N{}, M{};
public:
    explicit Matrix(const std::string &); //read from file

    explicit Matrix(int, int); //empty matrix

    explicit Matrix();

    void Print();

    void PrintToFile(const std::string &);

    int getN() const;

    int getM() const;

    void setData(int, int, long long);

    long long getData(int, int) const;

    Matrix operator+(const Matrix &);
//
//    Matrix operator*(const Matrix &);
//
    void Randomize(int, int); //random data
//
//    static void makeSum(int, int, const Matrix*, const Matrix*, Matrix*);
//    static void makeProd(int, int, const Matrix*, const Matrix*, Matrix*);
//
//    static void SumExecutor(const Matrix* initial, const Matrix* other, Matrix* result, std::queue<int> *Q);
//    static void ProdExecutor(const Matrix* initial, const Matrix* other, Matrix* result, std::queue<int> *Q);
};

#endif //LAB2_MATRIX_H
