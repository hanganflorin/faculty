//
// Created by Florin Hangan on 22/10/2018.
//


#include <fstream>
#include <vector>
#include <iostream>
#include "Matrix.h"
#include "utils.h"
#include <queue>
#include <thread>

//#define USE_SIMPLE
#define USE_THREADS

const int SIZE = 250; //size of the block to be calculated

std::vector<std::thread> threads;

Matrix::Matrix() : N(0), M(0) {

};

Matrix::Matrix(const std::string &fileName) {
    std::string filePath = "../files/" + fileName;
    std::ifstream is(filePath);
    is >> N >> M;

    data.resize((unsigned)N);
    for ( int i = 0 ; i < N ; i++ )
        data[i].resize((unsigned)M);

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            is >> this->data[i][j];
    is.close();
}

Matrix::Matrix(int _N, int _M) : N(_N), M(_M) {
    data.resize((unsigned)N);
    for ( int i = 0 ; i < N ; i++ )
        data[i].resize((unsigned)M);
}

void Matrix::Print() {
    std::cout << this->N << ' ' << this->M << '\n';
    for (const auto &i : data) {
        for (const auto &j : i)
            std::cout << j << ' ';
        std::cout << '\n';
    }
    std::cout << '\n';
}

void Matrix::PrintToFile(const std::string &fileName) {
    std::string filePath = "../files/" + fileName;
    std::ofstream os(filePath);
    os << this->N << ' ' << this->M << '\n';
    for (const auto &i : this->data) {
        for (const auto &j : i)
            os << j << ' ';
        os << '\n';
    }
    os << '\n';
    os.close();
}

int Matrix::getN() const {
    return N;
}

void Matrix::setData(int i, int j, long long val) {
    this->data[i][j] = val;
}

int Matrix::getM() const {
    return M;

}

long long Matrix::getData(int i, int j) const {
    return this->data[i][j];
}

void Matrix::Randomize(int left, int right) {
    for (auto &i : this->data) {
        for (auto &j : i) {
            j = generateRange(left, right);
        }
    }
}

Matrix Matrix::operator+(const Matrix &other) {
    if (other.getN() != this->N || other.getM() != this->M)
        throw "Incompatible";
    Matrix result(this->N, this->M);

#ifdef USE_SIMPLE
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            result.setData(i, j, this->data[i][j] + other.getData(i, j));
    return result;
#endif
#ifdef USE_THREADS
    int nr_threads = 0;
    for(int i = 0; i < this->N; i += SIZE)
        for ( int j = 0; j < this->M; j += SIZE )
        {
            nr_threads++;
            threads.emplace_back(&Matrix::SumExecutor, i, j, SIZE, this, &other, &result);
            for (auto& i : threads)
                i.join();
            threads.clear();
        }
    std::cout << nr_threads << " threads used\n";
    return result;
#endif
}

//solve for the block [i, i+size], [j, j+size]
void Matrix::SumExecutor(int i, int j, int size, const Matrix* m1, const Matrix* m2, Matrix* result) {
    for (int p1 = i; p1 <= i+size && p1 < m1->N; p1++ )
        for( int p2 = j; p2 <= j+size && p2 < m1->M; ++p2 )
            MakeSum(p1, p2, m1, m2, result);
}

void Matrix::MakeSum(int i, int j, const Matrix* m1, const Matrix *m2, Matrix *result) {
    result->setData(i, j, m1->getData(i, j) + m2->getData(i, j));
}

Matrix Matrix::operator*(const Matrix &other) {
    /*
   * A(N, M)
   * B(M, P)
   *   =>
   * C(N, P)
   */
    const int &N = this->N;
    const int &M = this->M;
    const int &P = other.getM();
    if (M != other.getN())
        throw "Incompatible";
    Matrix result(N, P);

#ifdef USE_SIMPLE
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            Matrix::MakeProd(i, j, this, &other, &result);
    return result;
#endif
#ifdef USE_THREADS
    int nr_threads = 0;
    for(int i = 0; i < this->N; i += SIZE)
        for ( int j = 0; j < this->M; j += SIZE )
        {
            nr_threads++;
            threads.emplace_back(&Matrix::ProdExecutor, i, j, SIZE, this, &other, &result);
            for (auto& i : threads)
                i.join();
            threads.clear();
        }
    std::cout << nr_threads << " threads used\n";
    return result;
#endif
}

void Matrix::ProdExecutor(int i, int j, int size, const Matrix* m1, const Matrix* m2, Matrix* result)
{
    for (int p1 = i; p1 <= i+size && p1 < m1->N; p1++ )
        for( int p2 = j; p2 <= j+size && p2 < m1->M; ++p2 )
            MakeProd(p1, p2, m1, m2, result);
}

void Matrix::MakeProd(int i, int j, const Matrix* m1, const Matrix *m2, Matrix *result)
{
    long long accumulated = 0;
    int M = m1->getM();
    for (int k = 0; k < M; ++k)
        accumulated += (m1->data[i][k] * m2->getData(k, j));
    result->setData(i, j, accumulated);
}
