//
// Created by Florin Hangan on 01/02/2019.
//

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <atomic>

#define MAX 1000
using namespace std;

bool b[MAX] = {false};
int N = 50;

vector<thread> threads;

void Erathostene() {
    for ( int i = 2; i * i <= N; i += 2 ) {
        if(b[i]) {
            threads.emplace_back([&](){
                mutex mtx;
                for ( int j = 2; i *j <= N; j++ ) {
                    lock_guard<mutex> guard(mtx);
                    b[i*j] = true;
                }
            });
        }
        if ( i == 2 )
            i--;
    }
    for ( auto &t: threads ) {
        t.join();
    }
}

int main() {
    b[2] = true;
    b[3] = true;
    Erathostene();
    for ( int i = 2; i <= N; ++i ) {
        if (b[i])
            cout << i << " ";
    }
    return 0;
}