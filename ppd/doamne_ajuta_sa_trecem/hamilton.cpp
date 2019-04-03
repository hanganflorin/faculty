//
// Created by Florin Hangan on 16/02/2019.
//

# include<vector>
# include<mutex>
# include<iostream>
# include<thread>
using namespace std;

mutex mtx;
void printPath(const vector<int> path) {
    lock_guard<mutex> guard(mtx);
    for ( const auto &x : path )
        cout << x << " ";
    cout << "\n";
}

void solve(const int n, const vector<vector<int>> &V, const vector<int> path) {
    if ( path.size() == n ) {
        printPath(path);
        return;
    }
    vector<thread> threads;
    int node = path.back();
    for ( const auto &x: V[node]) {
        if ( find(path.begin(), path.end(), x) == path.end() ) {
            vector<int> new_path(path);
            new_path.push_back(x);
            threads.emplace_back(solve, n, V, new_path);
        }
    }

    for ( auto &t : threads )
        t.join();
}

int main() {
    int n = 5;
    vector<vector<int>> V {{1, 4}, {0, 2}, {1, 3, 4}, {2, 4}, {0, 2, 3}};
    vector<int> path {2};
    solve(n, V, path);
    return 0;
}