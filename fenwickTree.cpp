// #include <iostream>
// #include <cstdio>
// #include <cstring>
// #include <cstdlib>
// #include <queue>
// #include <stack>
// #include <algorithm>
// #include <string>
// #include <map>
// #include <unordered_map>
// #include <set>
// #include <vector>
// #include <unistd.h>
// #include <time.h>
// using namespace std;

// #define lowbit(x) (x & (~x))

// class FenwickTree
// {
// public:
//     FenwickTree(int size) : n(size), c(n + 1) {}
//     void add(int i, int x)
//     {
//         while (i <= n)
//         {
//             c[i] += x;
//             i += lowbit(i);
//         }

//         return; //原数组修改，c[i] -> c[i+lowbit(i)] ->c [i+lowbit(i+lowbit(i))]
//     }
//     int query(int x)
//     {
//         int sum = 0;
//         while (x)
//         {
//             sum += c[x];
//             x -= lowbit(x);
//         }

//         return sum;
//     }

//     void output()
//     {
//         // int len = 0;
//         // for (int i = 1; i <= n; i++)
//         // {
//         //     printf("%5d", i);
//         //     len += 1;
//         // }
//         // printf("\n");
//         // for (int i = 0; i < len + 6; i++)
//         // {
//         //     printf("=");
//         // }
//         // for (int i = 1; i <= n; i++)
//         // {
//         //     printf("%5d", c[i]);
//         // }

//         printf("\n");
//         return;
//     }

// private:
//     int n; //下标上限
//     vector<int> c;
// };

// int main()
// {
//     int n, a;
//     cin >> n;
//     FenwickTree tree(n);
//     for (int i = 1; i <= n; i++)
//     {
//         cin >> a;
//         tree.add(i, a);
//     }
//     tree.output();
//     int ind, val;
//     while (cin >> ind >> val)
//     {
//         cout << "change " << ind << " to " << val << endl;
//         tree.add(ind, val - (tree.query(ind) - tree.query(ind - 1)));
//         tree.output();
//     }
//     return 0;
// }
