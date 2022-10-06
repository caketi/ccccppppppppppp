#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>
#include <string>
#include <map>
#include <unordered_map>
#include <set>
#include <vector>

#include <time.h>
using namespace std;
#define MAX_N 100
int mu[MAX_N + 5] = {0};
int prime[MAX_N + 5] = {0};

void init_prime(int n)
{
    mu[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        if (!prime[i])
        {
            prime[++prime[0]] = i;
            mu[i] = -1;
        }
        for (int j = 1; j <= prime[0]; j++)
        {
            if (i * prime[j] > n)
                break;
            prime[i * prime[j]] = 1;
            if (i % prime[j] == 0)
                break;
            mu[i * prime[j]] = -mu[i];
        }
    }
    return;
}

int is_prime(int x)
{
    if (x <= 1)
        return 0;
    for (int i = 2; i * i <= x; i++)
    {
        if (x % i == 0)
            return 0;
    }
    return 1;
}
int gcd(int a, int b)
{
    if (b)
        return gcd(b, a % b);
    return a;
}

// 给定n , m  求 1<=x<=n  1<=y<=m && gcd(x,y)为质数的(x,y)有多少对
int main()
{
    int n;
    cin >> n;
    init_prime(n);
    for (int i = 1; i <= n; i++)
    {
        cout << "mu[" << i << "] = " << mu[i] << endl;
    }
    // int n, m, ans = 0;
    // cin >> n >> m;
    // for (int i = 1; i <= n; i++)
    // {
    //     for (int j = 1; j <= m; j++)
    //     {
    //         if (!is_prime(gcd(i, j)))
    //             continue;
    //         ans += 1;
    //         cout << i << " " << j << endl;
    //     }
    // }
    // cout << ans << endl;
    return 0;
}