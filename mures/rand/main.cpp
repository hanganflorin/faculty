//I. Enter an initial variable X positive integer.
//II. Multiply X by variable "a", which should be at least 5 digits long.
//III. Divide a*X by value p (positive integer).
//IV. Take the fraction part of the division as a first pseudo-random number.
//V. Make the number from step IV into integer by a necessary multiplication and use it in step II.
//VI. Step II-V are repeated to generate more pseudo-random numbers.

#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;

int random_generator();
long long seed;

int main(int argc, char *argv[])
{
    seed = time(0);
    for(int i = 0; i < 1000; ++i )
        cout << random_generator() << "\n";
    return 0;
}

int random_generator()
{
    int a = 324223423; // this should be at least 5 digits long
    int p = 30977; // prime number
    int n = 12;

    for(int i = 0; i < n; i++)
        seed=(1LL*a*seed % p);

    return seed;
}