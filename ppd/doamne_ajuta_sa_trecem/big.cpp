#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <atomic>
#define MAX 10
using namespace std;


void work(int digit, int b[], int m, int l, int x[MAX][MAX]) {
    int carry = 0;
    for (int i = m-1; i >= 0; i--)
    {
        x[l][i + l] = b[i] * digit + carry;
        carry = x[l][i + l] / 10;
        x[l][i + l] %= 10;
        if (i == 0 && carry > 0)
            x[l][l - 1] = carry;
    }
}

void work2(int x[MAX][MAX], int c, int n)
{
    for (int i = 0; i < n; i++)
        x[n][c] += x[i][c];
}

int main() {
    int a[] = { 1,2,3 };
    int b[] = { 4,5,6 };
    int x[MAX][MAX] = {0};
    int n = 3;
    int m = 3;

    thread ths[n];
    for (int i = 0; i < n; ++i)
        ths[i] = thread(work, a[i], b, m, i, x);
    for (int i = 0; i < n; ++i)
        ths[i].join();

    thread ths2[m+n];
    for (int i = 0; i < n + m; ++i)
        ths2[i] = thread(work2, x, i, n);
    for (int i = 0; i < n + m; ++i)
        ths2[i].join();

    for (int i = 0; i < n + m; ++i) {
        x[n][i] = x[n][i] + (x[n][i + 1] / 10);
        x[n][i] %= 10;
        cout << x[n][i];
    }

    return 0;
}