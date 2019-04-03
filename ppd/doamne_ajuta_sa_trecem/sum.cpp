//
// Created by Florin Hangan on 18/02/2019.
//

#include <tuple>
#include <vector>
#include <future>
#include <mutex>
#include <iostream>

using namespace std;

mutex mtx;
void printVector(const vector<int> path) {
    lock_guard<mutex> guard(mtx);
    for ( const auto &x : path )
        cout << x << " ";
    cout << "\n";
}

void work(const int N, const vector<int> &current_set, const int sum) {
    if ( sum > N )
        return;
    if ( current_set.size() > N )
    {
        if ( sum == N )
            printVector(current_set);k;l
        return;
    }
    int last = 0;
    if ( !current_set.empty() )
        last = current_set.back();
    vector<thread> threads;
    for ( int i = last; i < N; ++i )
    {
        vector<int> next_set(current_set);
        next_set.push_back(i);
        threads.emplace_back(work, N, next_set, sum+i);
    }
    for ( auto &t: threads )
        t.join();
}

int main() {
    int N = 6;
    vector<int> empty;
    work(N, empty, 0);
    return 0;
}