#include <algorithm>
#include <iostream>

using namespace std;
class dp3{
    // 1027 方格取数，从a到b走了两次，找出两条路径使得取得数字和为最大
    // 只走一次: f[i,j]表示所有从(1,1)走到(i,j)的路径的最大值
    //           f[i,j] = max(f[i-1,j] + w[i,j], f[i,j-1] + w[i,j])
    // 走两次: f[i1,j1,i2,j2]表示所有从(1,1),(1,1)分别走到(i1,j1),(i2,j2)的路径的最大值
    // 如何处理“同一个格子不能被重复选择”
    // 只有在i1+j1 == i2 + j2时，两条路径的格子才可能重合
    // f[k, i1, i2]表示所有从(1,1),(1,1)分别走到(i1, k-i1), (i2, k-i2)的路径的最大值
    // k表示两条路线当前走到的格子的横纵坐标之和
    // k = i1 + j1 = i2 + j2
const static int N = 15;
int n;
int w[N][N];
int f[N*2][N][N];

void test(){
    scanf("%d", &n);
    int a, b, c;
    while(cin >> a >> b >> c, a || b || c) w[a][b]=c;
    for(int k = 2; k <= n + n; k ++){
        for(int i1 = 1; i1 <= n; i1++){
            for(int i2 = 1; i2 <= n; i2++){
                int j1 = k - i1, j2 = k - i2;
                if(j1 >= 1 && j1 <= n && j2 >=1 && j2 <= n){
                    int t = w[i1][j1];
                    if(i1 != i2 ) t += w[i2][j2];
                    int &x = f[k][i1][i2];
                    x = max(x, f[k-1][i1-1][i2-1] + t);
                    x = max(x, f[k-1][i1-1][i2] + t);
                    x = max(x, f[k-1][i1][i2-1] + t);
                    x = max(x, f[k-1][i1][i2] + t);
                }
            }
            printf("%d\n", f[n+n][n][n]);
        }
    }
}

};

class dp2 {
    // acwing 1018. 最低通行费 左上进，右下出 没穿越中间一个小方格 花费1个单位时间 必须在2N-1个单位时间穿越出去
  const static int N = 110, INF = 1e9;
  int n;
  int w[N][N];
  int f[N][N];
  void test() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++){
        if(i == 1 && j == 1) f[i][j] = w[i][j];  //特判左上角
        else {
            f[i][j] = INF;
            if(i > 1) f[i][j] = min(f[i][j], f[i-1][j] + w[i][j]); // 只有不在第一行才可以从上边下俩
            if(j > 1) f[i][j] = min(f[i][j], f[i][j-1] + w[i][j]); // 只有不在第一列才可以从左边下来
        }
        printf("%d\n", f[n][n]);
      }
    }
  }
};
// acwing 1017.摘花生
const int N = 110;
int n, m;
int w[N][N];
int f[N][N];
// 2      2组数据
// 2 2    花生苗的行数和列数
// 1 1
// 第一个数据从北向南描述每行花生苗的情况，第二个数据从西向东描述该行花生数目 3
// 4 2 3 2 3 4 1 6 5

// 8
// 16
int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        scanf("%d", &w[i][j]);
      }
    }

    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        f[i][j] = max(f[i - 1][j], f[i][j - 1]) + w[i][j];
      }
    }
    printf("%d\n", f[n][m]);
  }
  return 0;
}
