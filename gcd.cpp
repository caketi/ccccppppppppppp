#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <stack>
#include <algorithm>
#include <string>
#include <map>
#include <unordered_map>
#include <set>
#include <vector>
#include <unistd.h>
#include <time.h>
using namespace std;

int count_prime(int n)
{
    int prime[n + 1];
    memset(prime, 0, sizeof(prime));
    prime[0] = prime[1] = 1;
    for (int i = 2; i * i <= n; i++)
    {
        if (prime[i])
            continue;
        for (int j = i * i; j <= n; j += i)
            prime[j] = 1;
    }
    int cnt = 0;
    for (int i = 2; i <= n; i++)
        cnt += (prime[i] == 0);
    return cnt;
}
long long frac(long long n, long long m)
{
    long long ans = 1;
    for (int i = 2; i <= n; i++)
        ans = ans * i % n;
    return ans;
}
int numPrimeArrangements(int n)
{
    int m = count_prime(n), mod_num = 1e9 + 7;
    return frac(m, mod_num) * frac(n - m, mod_num) % mod_num;
}

int phi(int n)
{ //返回的结果是与n互质且小于n的个数
    int x = 2, ans = n;
    while (x * x <= n)
    {
        if (n % x == 0)
            ans -= ans / x;
        while (n % x == 0)
            n /= x;
        x += 1;
    }
    if (n != 1)
        ans -= ans / n;
    return ans;
}

int gcd(int a, int b)
{
    cout << "gcd (" << a << ", " << b << ") = ";
    if (b)
        return gcd(b, a % b);
    return a;
}
string gcdOfStrings(string str1, string str2)
{
    if (str1 + str2 != str2 + str1)
        return "";
    int r = gcd(str1.size(), str2.size());
    return str1.substr(0, r);
}

int ex_gcd(int a, int b, int &x, int &y)
{
    if (b == 0)
    {
        x = 1, y = 0;
        return a;
    }
    int r = ex_gcd(b, a % b, y, x);
    y -= a / b * x;
    return r;
}
int main()
{
    int n;
    while (cin >> n)
    {
        cout << "phi(" << n << ") = " << phi(n) << endl;
    }
    return 0;

    // int a, b;

    // while (cin >> a >> b)
    // {
    //     cout << gcd(a, b) << endl;
    //     int x, y;
    //     int c = ex_gcd(a, b, x, y);
    //     cout << a << " * " << x << " + " << b << " * " << y << " = " << c << endl;
    // }
}