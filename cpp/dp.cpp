#include <iostream>
#include <algorithm>
using namespace std;

// acwing 1017.摘花生
 const int N = 110;
 int n, m;
 int w[N][N];
 int f[N][N];
// 2      2组数据
// 2 2    花生苗的行数和列数
// 1 1     第一个数据从北向南描述每行花生苗的情况，第二个数据从西向东描述该行花生数目
// 3 4
// 2 3
// 2 3 4
// 1 6 5

// 8
// 16
 int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= m; j++){
                scanf("%d", &w[i][j]);
            }
        }

        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= m; j++){
                f[i][j] = max(f[i-1][j], f[i][j-1])+w[i][j];
            }
        }
        printf("%d\n", f[n][m]);
    }
    return 0;
 }
