//linear congruential generator.
//r = ((r * 7621) + 1) % 32768; - recursive formula

#include <iostream>
#include <ctime>
#define MOD 12423

int random_recursive(int n){
    if ( n == 0 )
        return 1;
    return ((random_recursive(n-1) * 7621) + 1) % 32768;
}

int seed;

int random_generator()
{
    //seed is the number of recursive calls of random_recursive()
    seed = seed % MOD; // % MOD to lower the value of seed
    int r = random_recursive(seed);
    seed += r; // after each call modify the seed
    return r;
}

int main() {
    seed = time(0); //start seed with current time

    for ( int i = 0; i < 100; ++i )
        std::cout << random_generator() << '\n';
    return 0;
}

