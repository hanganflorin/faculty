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

    void Randomize(int, int); //random data

    Matrix operator+(const Matrix &);
    static void SumExecutor(int i, int j, int size, const Matrix* m1, const Matrix* m2, Matrix* result);
    static void MakeSum(int i, int j, const Matrix* m1, const Matrix *m2, Matrix *result);

    Matrix operator*(const Matrix &);
    static void ProdExecutor(int i, int j, int size, const Matrix* m1, const Matrix* m2, Matrix* result);
    static void MakeProd(int i, int j, const Matrix* m1, const Matrix *m2, Matrix *result);

};

#endif //LAB2_MATRIX_H
