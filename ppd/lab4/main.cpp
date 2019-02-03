#include <mutex>
#include <condition_variable>
#include <queue>
#include <thread>
#include <iostream>
#include <iomanip>
#include "utils.h"

const int T[] = {1, 3, 5, 10, 25, 50, 100};
const int Cases[] = {100, 300, 500, 750, 1000, 1500, 3000};

std::mutex mx;
std::condition_variable cv;
std::queue<std::tuple<int, int, int>> queue; // NOLINT(cert-err58-cpp)

std::vector< std::vector<int> > A, B, C, Result;
int N;
bool finished;

inline void initMatrices();
inline void producer(int, int);
inline void consumer();
void pp(std::vector<std::vector<int>> &x) {
    std::cout << '\n';
    for (const auto& i : x) {
        for (const auto& j : i) {
            std::cout << j << ' ';
        }
        std::cout << '\n';
    }
}

int main() {
    for (int testNumber = 0; testNumber < 7; ++testNumber) {
        N = Cases[testNumber];
        for (int threadNumber : T) {
            std::cout << "Test suite: #" << std::setw(2) << testNumber << " matrix sizes: " << std::setw(4) << N << " thread numbers: " << std::setw(3) << threadNumber << " Initializing matrices";
            initMatrices();
//            pp(A);
//            pp(B);
//            pp(C);
//            pp(Result);
            auto start = std::chrono::high_resolution_clock::now();
            std::vector<std::thread> producers, consumers;
            for (int i = 0; i < std::min(N, threadNumber); ++i) {
                producers.emplace_back(producer, i, threadNumber);
            }
            for (int i = 0; i < std::min(N, threadNumber); ++i) {
                consumers.emplace_back(consumer);
            }
            for (auto &producer : producers) {
                producer.join();
            }
            {
                std::lock_guard<std::mutex> lk(mx);
                finished = true;
            }
            cv.notify_all();
            for (auto &consumer : consumers) {
                consumer.join();
            }
//            pp(A);
//            pp(B);
//            pp(C);
//            pp(Result);
            auto finish = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = finish - start;
            std::cout << " TOTAL TIME: " << elapsed.count() << '\n';
        }
    }
}

inline void initMatrices() {
    A = std::vector< std::vector<int> > (static_cast<unsigned long>(N), std::vector<int> (N, 0));
    B = std::vector< std::vector<int> > (static_cast<unsigned long>(N), std::vector<int> (N, 0));
    C = std::vector< std::vector<int> > (static_cast<unsigned long>(N), std::vector<int> (N, 0));
    Result = std::vector< std::vector<int> > (static_cast<unsigned long>(N), std::vector<int> (N, 0));
    for (auto &i : A)
        for (int &j : i)
            j = generateRange(1, 100000);

    for (auto &i : B)
        for (int &j : i)
            j = generateRange(1, 100000);

    for (auto &i : C)
        for (int &j : i)
            j = generateRange(1, 100000);
}

inline void producer(int line, int T) {
    for (int i = line; i < N; i += T) {
        for (int j = 0; j < N; ++j) {
            int accumulator = 0;
            for (int k = 0; k < N; ++k) {
                accumulator += A[i][k] * B[k][j];
            }
            {
                std::lock_guard<std::mutex> lockGuard(mx);
                queue.push(std::make_tuple(i, j, accumulator));
            }
            cv.notify_all();
        }
    }
}

inline void consumer() {
    while (true) {
        std::unique_lock<std::mutex> uniqueLock(mx);
        cv.wait(uniqueLock, []
            {
            return finished || !queue.empty();
            });
        if (finished)
            break;
        std::tuple<int, int, int> el = queue.front();
        queue.pop();
        int i = std::get<0>(el);
        int j = std::get<1>(el);
        int x = std::get<2>(el);
        for (int k = 0; k < N; ++k) {
            Result[i][k] += x * C[j][k];
        }
    }
}