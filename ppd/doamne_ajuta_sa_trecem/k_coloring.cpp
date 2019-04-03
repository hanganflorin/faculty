//
// Created by Florin Hangan on 15/02/2019.
//

#include <tuple>
#include <vector>
#include <future>
#include <mutex>
#include <iostream>

using namespace std;


mutex mtx;
void printConfiguration(const vector<int> configuration) {
    lock_guard<mutex> guard(mtx);
    for ( const auto& x : configuration )
        cout << x << " ";
    cout << "\n";
}

bool check(const int n, const int k, const vector<tuple<int, int>>& restrictions, vector<int> configuration) {
    for ( const auto& r : restrictions ) {
        int a = get<0>(r);
        int b = get<1>(r);
        if ( configuration[a] == configuration[b] )
            return false;
    }
    return true;
}

void solve(const int n, const int k, const vector<tuple<int, int>>& restrictions, vector<int> configuration) {

    if ( configuration.size() == n ) {
        if (check(n, k, restrictions, configuration))
            printConfiguration(configuration);
        return;
    }
    vector<thread> threads;
    for (int i = 1; i <= k; ++i ) {
        vector<int> new_config(configuration);
        new_config.push_back(i);
        threads.emplace_back(solve, n, k, restrictions, new_config);
    }
    for ( auto &t : threads )
        t.join();
}


int main() {

    int k = 3; //colors
    int n = 5; //objects
    vector<tuple<int, int>> restrictions {make_tuple(1, 3), make_tuple(4, 2), make_tuple(1, 2), make_tuple(3, 4), make_tuple(3, 2), make_tuple(0, 2), make_tuple(0, 4), make_tuple(0, 1)};
    vector<int> empty;
    solve(n, k, restrictions, empty);
    return 0;
}