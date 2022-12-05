#include <iostream>
#include <stdio.h>

using namespace std;
// template<class T>
// class Array{
//   private:
//   T *A;
//   int size;
//   int length;
//   public:
//   Array(){
//     size = 10;
//     A = new T[10];
//     length = 0;
//   }
//   Array(int sz){
//     size = sz;
//     length = 0;
//     A= new T[size];
//   }
//   ~Array(){
//     delete []A;
//   }
//   void Display();
//   void Insert(int index,T x);
//   T Delete(int index);
// };
// template<class T>
// void Array<T>::Display(){
//     for(int i = 0; i < length; i++){
//         cout << A[i] << " ";
//     }
//     cout << endl;
// }
// template<class T>
// void Array<T>::Insert(int index, T x){
//     if(index >= 0 && index <= length){
//         for(int i = length - 1; i >= index; i--){
//             A[i+1] = A[i];
//         }
//         A[index] = x;
//         length++;
//     }
// }
// template<class T>
// T Array<T>::Delete(int index){
//     T x = 0;
//     if(index >= 0 && index < length){
//         x = A[index];
//         for(int i = index; i < length-1; i++){
//             A[i] = A[i+1];
//         }
//         length --;
//     }
//     return x;
// }
// int main(){
//     Array<char> arr(10);
//     arr.Insert(0, 'f');
//     arr.Insert(0, '6');
//     arr.Insert(1,'a');
//     arr.Display();
//     cout << arr.Delete(0) << endl;
//     arr.Display();
// // find duplicate elements in unsorted array
// int b[500000];
// int a[5] = {91,91,3,3,1};
// for(int i = 0; i < 4; i++){
//     if(a[i] == a[i+1]){
//         int j = i + 1;
//         while(a[j] == a[i]) j++;
//         printf("%d is appearing %d times\n", a[i], j-i);
//         i = j - 1;
//     }
// }
// for(int i = 0; i <= 4; i++){
//     b[a[i]]++;
// }
// for(int i = 0; i <= 4; i++){
//    if(b[i] == 0) printf("%d is missing elem", i);
//     if(b[i] > 1) printf("duplicate ele: %d count: %d", i, b[i]);
// }
// for(int i = 0; i < 4; i++){
//     int count = 1;
//     if(a[i] != -1){
//         for(int j = i+1; j < 4; j++){
//             if(a[i] == a[j]){
//                 count++;
//                 a[j] = -1;
//             }
//         }
//        if(count>1) printf("duplicate ele: %d count: %d", a[i], count);
//     }
// }
// // find a pair with sum k (a+b = k)
// int a[5] = {5,3,4,5,6};
// int i = 0, j = 4, k = 10;
// while(i < j){
//     if(a[i] + a[j] == k){
//         printf("%d+%d=%d", a[i], a[j], k);
//         i++;
//         j--;
//     }
//     else if(a[i] + a[j] < k){
//         i++;
//     }else {
//         j--;
//     }
// }
// // finding MAX and MIN in a single scan
// int A[3] = {5,82,3};
// int min = A[0];
// int max = A[0];
// for(int i = 1; i < 3; i++){
//     if(A[i] < min){
//         min = A[i];
//     }else if(A[i] > max){
//         max = A[i];
//     }
// }
// printf("MAX: %d MIN: %d", max, min);

// // Length of string
// char s[] = "caketiPotato";
// int i;
// for(i = 0; s[i] != '\0'; i++){

// }
// printf("Length of string : %d ", i);
// // 两极反转 A-Z 65-90 a-z 97-122
// char A[] = "caketiPotato";
// int i;
// for(i = 0; A[i] != '\0'; i++){
//     if(A[i] >= 'A' && A[i] <= 'Z'){ // 65 90
//         A[i] += 32;
//     }else if(A[i] >= 'a' && A[i] <= 'z'){
//         A[i] -= 32; // 97-122
//     }
// }
// for(char s : A){
//     printf("%c ", s);
// }
// }

// kruskal's program
#define I 999999
int edges[3][9] = {{1, 1, 2, 2, 3, 4, 4, 5, 5},
                   {2, 6, 3, 7, 4, 5, 7, 6, 7},
                   {25, 5, 12, 10, 8, 16, 14, 20, 18}};

int set[8] = {-1, -1, -1, -1, -1, -1, -1, -1};
int included[9] = {0};
int t[2][6];
void join(int u, int v) {
  if (set[u] < set[v]) {
    set[u] += set[v];
    set[v] = u;
  } else {
    set[v] += set[u];
    set[u] = v;
  }
}
int find(int u) {
  int x = u, v = 0;
  while (set[x] > 0) {
    x = set[x];
  }
  while (u != x) {
    v = set[u];
    set[u] = x;
    u = v;
  }
  return x;
}

int pow(int m, int n) {
  if (n == 0) {
    return 1;
  }
  return pow(m, n - 1) * m;
}
int pow1(int m, int n) {
  if (n == 0) {
    return 1;
  }
  if (n % 2 == 0) {
    return pow(m * m, n / 2);
  } else {
    return m * pow(m * m, (n - 1) / 2);
  }
}

int main() {
  // finding duplicate elem in string
  char a[] = "caketipotato";
  long int h = 0, x = 0;
  for (int i = 0; a[i] != '\0'; i++) {
    x = 1;
    x = x << a[i] - 97;
    if (x & h > 0) {
      printf("%c is duplicated", a[i]);
    } else {
      h = x | h;
    }
  }
  // int i, j, k, u , v, min=I,  e=9;
  // int n = 7;
  // i = 0;
  // while(i <n-1){
  //     min = I;
  //     for(j = 0; j < e; j++){
  //         if(included[j] == 0 && edges[2][j] < min){
  //             min = edges[2][j];
  //             u = edges[0][j];
  //             v = edges[1][j];
  //             k = j;
  //         }
  //     }
  //     if(find(u) != find(v)){
  //         t[0][i] = u;
  //         t[1][i] = v;
  //         join(find(u), find(v));
  //         i++;
  //     }
  //     included[k] = 1;
  // }
  // for(i = 0; i < n-1; i++){
  //     cout << "(" <<t[0][i] << ","<<t[1][i] <<")"<<endl;
  // }
}