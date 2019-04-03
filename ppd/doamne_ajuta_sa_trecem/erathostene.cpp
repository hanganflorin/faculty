//
// Created by Florin Hangan on 01/02/2019.
//

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <atomic>
#include <math.h>

#define MAX 1001
using namespace std;


bool b[MAX];
int N = 1000;

vector<thread> threads;

void Erathostene(int n) {
    for ( int i = 2; i * i <= n; i += 2 ) {
        if(!b[i])
            for ( int j = 2; j * i <= n; ++j )
                b[i*j] = true;

        if ( i == 2 )
            i--;
    }
}

void work(int p){
    for ( int i = 2; i * p <= N; ++i )
        b[p*i] = true;
}

int main() {

//    for ( int i = 2; i <= N; ++i )
//        b[i] = true;
    b[0] = b[1] = true;

    Erathostene((int)sqrt(N));

    for ( int i = 2; i * i <= N; i++)
        if (!b[i])
            threads.emplace_back(work, i);

    for ( auto& t : threads )
        t.join();



    for ( int i = 2; i <= N; ++i ) {
        if (!b[i])
            cout << i << " ";
    }
    return 0;
}