#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <stack>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <assert.h>
#include <time.h>
#include <math.h>
using namespace std;
void fnc(char* &temp){
    char *p = (char*)malloc(64);
    memset(p, 0, 64);
    strcpy(p, "xia");
    temp = p;
}
void test02(){
    char* mp = NULL;
    fnc(mp);
    cout << mp;
}

const int a = 1;
void test()
{
    int *p = (int *)&a;
    //  a = 200;
    *p = 11;
    printf("%d\n", a);
}
int main()
{
    // 常量zhedie
    // test();
    // 禁止优化
    volatile const int b = 2;

    int *p = (int *)&b;
    *p = 200;
    printf("%d\n", b);
    printf("%d\n", *p);
    test02();
    system("pause");
}

//对应二进制位不同的位置的数目
int hamingDistance(int x, int y)
{
    x ^= y;
    int cnt = 0;
    while (x)
    {
        x &= (x - 1); //踢掉x二进制末尾的1
        cnt += 1;
    }
    return cnt;
}

string convertToBase7(int num)
{
    if (num == 0)
        return "0";
    int flag = (num < 0);
    string s = "";
    while (num)
    {
        s += char(abs(num) % 7 + '0'); // 留下个位
        num /= 7;                      // 踢掉个位
    }
    if (flag)
        s += "-";
    reverse(s.begin(), s.end());
    return s;
}

// n = 10 --- 4 小于10的质数一共4个，2,3,5,7
int countPrimes(int n)
{
    int *prime = new int[n + 1];
    for (int i = 0; i < n; i++)
        prime[i] = 0;
    for (int i = 2; i * i < n; i++)
    {
        if (prime[i])
            continue;
        for (int j = 2 * i; j < n; j += i)
        {
            prime[j] = 1;
        }
    }
    int cnt = 0;
    for (int i = 2; i < n; i++)
        cnt += (prime[i] == 0);
    delete[] prime;
    return cnt;
}

// int main(){
//     // cout << countPrimes(10) << endl;
//     cout << convertToBase7(12)<<endl;
// }