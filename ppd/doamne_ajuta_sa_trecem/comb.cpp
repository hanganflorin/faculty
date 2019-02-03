//
// Created by Florin Hangan on 29/01/2019.
//

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <atomic>
using namespace std;

const int N = 7;
const int K = 3;

atomic<int> cnt(0);

mutex mtx;
void printVector(const vector<int>& x) {
    lock_guard<mutex> guard(mtx);
    for (const auto& i : x)
        cout << i << ' ';
    cout << '\n';
}

inline bool predicate(vector<int> const &v) {
    return true;
}

inline int getNextPosition(vector<int> const &given_set, vector<int> const &current_set) {
    if ( current_set.empty() )
        return 0;

    int lastElement = current_set.back();
    for ( int i = 0; i < given_set.size(); i++ )
        if ( given_set[i] == lastElement )
            return i+1;
}

void subset(vector<int> const &given_set, vector<int> const &current_set) {
    if ( current_set.size() >= K )
    {
        if ( predicate(current_set) ) {
            cnt++;
            printVector(current_set);
        }
        return;
    }
    vector<thread> threads;
    for(int i = getNextPosition(given_set, current_set); i < given_set.size(); i++ )
    {
        vector<int> next_set(current_set);
        next_set.push_back(given_set[i]);
        threads.emplace_back(subset, given_set, next_set);
    }

    for (auto& t : threads)
        t.join();
}

int main()
{
    vector<int> given_set = {1, 2, 3, 4, 5, 6};
    vector<int> empty;
    subset(given_set, empty);
    cout << cnt << "\n";
    return 0;
}