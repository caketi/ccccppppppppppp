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
#include <unordered_map>
#include <vector>
#include <functional>
using namespace std;




template <typename T>
class Heap : public vector<T>
{
private:
    function<bool(T, T)> cmp;

public:
    template <typename Func_T>
    Heap(Func_T cmp) : cmp(cmp) {}
    void push(const T &a)
    {
        this->push_back(a);
        push_heap(this->begin(), this->end(), cmp);
        return;
    }
    T pop()
    {   
        T ret = top();
        pop_heap(this->begin(), this->end(), cmp);
        this->pop_back();
        return ret;
    }
    T &top() { return this->at(0); }
};

int main()
{
    Heap<int> h1{less<int>()};    // 大顶堆
    Heap<int> h2{greater<int>()}; // 小顶堆
    h1.push(3);
    h1.push(2);
    h1.push(4);
    h1.push(1);
    h2.push(3);
    h2.push(2);
    h2.push(4);
    h2.push(1);
    while (h1.size())
    {
        cout << h1.top() << " ";
        h1.pop();
    }
    cout << "" << endl;

    while (h2.size())
    {
        cout << h2.top() << " ";
        h2.pop();
    }
    return 0;
}

const int maxn = 2e4 + 10;
struct heap1{
    int heap[maxn];
    int heapsize;
    heap1(){
        heapsize = 0;
    }
    int top(){
        return heap[1];
    }
    void shift(int id){
        if( id == 1) return;
        if(heap[id] > heap[id/2]){
            swap(heap[id], heap[id/2]);
            shift(id/2);
        }
    }
    void push(int x){
        heap[++heapsize] = x;
        shift(heapsize);
    }
    void push_down(int id){
        if(id * 2 > heapsize) return;
        int k = id;
        if(heap[id] < heap[id*2]) k = id * 2;
        if( id * 2 + 1 <= heapsize && heap[k] < heap[id*2+1]) k = id * 2+1;
        if(id == k) return;
        swap(heap[id], heap[k]);
        push_down(k);
    }
    void pop(){
        heap[1] = heap[heapsize--];
        push_down(1);
    }
};

// //找中最小的k个数
vector<int> getLeastNumbers(vector<int> &arr, int k){
    Heap<int> h{less<int> ()};
    for( auto x : arr){
        h.push(x);
        if( h.size() > k) h.pop();
    }
    return h;
}

int lastStoneWeight(vector<int> &stones){
    Heap<int> h{less<int>()};
    for(auto x:stones){
        h.push(x);
    }
    while(h.size() > 1){
        int y = h.top(); h.pop();
        int x = h.top(); h.pop();
        if(x == y) continue;
        h.push(y-x);
    }
    if ( h.size() == 0) return 0;
    return h.top();
}

// 返回第k大元素-----每次和最小值比，谁小谁zou,小堆

Heap<int> h{greater<int>()};
int k;
int add( int val){
    h.push(val);
    if( h.size() > k) h.pop();
    return h.top();
}
void KthLargest(int k, vector<int>& nums){
    for(auto x :nums){
        add(x);
    }
    return ;
}



// struct CMP
// {
//     bool operator()(vector<int> a, vector<int> b)
//     {
//         return a[0] + a[1] < b[0] + b[1];
//     }
// };
// vector<vector<int> > kSmallestPairs(vector<int> &nums1, vector<int> &nums2, int k)
// {
//     CMP less_than;
//     Heap<vector<int> > h{less_than};
//     vector<int> temp[2];
//     for (auto x : nums1)
//     {
//         for (auto y : nums2)
//         {
//             temp[0] = x, temp[1] = y;
//             if (h.size() < k || less_than(temp, h.top()))
//             {
//                 h.push(temp);
//                 if (h.size() > k)
//                     h.pop();
//             }
//             else
//             {
//                 break;
//             }
//         }
//     }
// }

vector<string> topKFrequent(vector<string>& words, int k){
    unordered_map<string, int> freq;
    for( auto x : words) freq[x] += 1;
    auto cmp = [&freq](string a, string b)->bool{
        if(freq[a] - freq[b]) return freq[a] > freq[b];
        return a < b;
    };
    Heap<string> h{cmp};
    for(auto x : freq){
        h.push(x.first);   
        if( h.size() > k) h.pop();
    }
    sort(h.begin(), h.end(), cmp);
    return h;
}


// int maximumScore(int a, int b, int c){
//     if( a > b) swap(a,b);
//     if( a> c) swap(a,c);
//     if( b> c) swap(b,c);
//     int ans = 0;

//     // step1
//     int cnt1 = min(c-b, a);
//     a-=cnt1;
//     c-=cnt1;
//     ans+=cnt1;

//     //step2
//     if(a!=0){
//         if(a%2==1) a-=1;
//         b-=a/2;
//         c-=a/2;
//         ans+=a;
//     }

//     //step3
//     ans+=b;
//     return ans;
// }

// 积压订单 leetcode 销售 大顶堆 购买小顶堆
// strcut CMP1{
//     bool operator()(vector<int> a, vector<int> b){
//         return a[0] < b[0];
//     }
// };

// struct CMP2 {
//     bool operator()(vector<int> a, vector<int> b){
//         return a[0] > b[0];
//     }
// };

// int getNumberOfBacklogOrders(vector<vector<int>>& orders){
//     Heap<vector<int>> buy{CMP1()}, sell{CMP2()};
//     for(auto x : orders){
//         if(x[2] == 0){
//             while(x[1]!=0&&sell.size()&& sell[0][0]<=x[0]){
//                 int cnt = min(x[1], sell[0][1]);
//                 x[1] -= cnt;
//                 sell[0][1] -= cnt;
//                 if(sell[0][1] == 0) sell.pop();
//             }
//            if(x[1] != 0) buy.push(x);
//         } else {
//             while(x[1] !=0 && buy.size() && buy[0][0] >= x[0]){
//                 int cnt = min(x[1], buy[0][1]);
//                 x[1] -= cnt;
//                 buy[0][1] -= cnt;
//                 if(buy.top[1] == 0) buy.pop();
//             }
//             if( x[1] != 0) sell.push(x);
//         }
//     }
//     int sum = 0;
//     int mod = 100000007;
//     for(auto x : buy){
//         sum = (sum + x[1]) % mod;
//     }
//     for(auto x : sell){
//         sum = (sum + x[1]) % mod;
//     }
//     return sum;
// }



int nthUglyNumber(int n){
    Heap<long long> h{greater<long long>()};
    long long  ans = 0;
    h.push(1);
    while(n--){
        ans = h.top();
        h.pop();
        if(ans % 5 == 0){
            h.push(ans * 5);
        }
        if (ans % 3 == 0){
            h.push(ans * 5);
            h.push(ans * 3);
        } else{
            h.push(ans * 5);
            h.push(ans * 3);
            h.push(ans * 2);
        }
    }
    return ans;
}


int nthSuperUglyNumber(int n, vector<int>& primes){
    vector<int> p(primes.size());
    vector<int> data;
    data.push_back(1);
    int ans = 1;
    while(data.size() != n){
        ans = primes[0] * data[p[0]];
        for(int i = 1; i < primes.size(); i++){
            ans = min(ans, primes[i] * data[p[i]]);
        }
        for(int i = 0; i < primes.size(); i++){
            if(primes[i] * data[p[i]] == ans) p[i]++;
        }
        data.push_back(ans);
    }
    return ans;
}

//有序序列中位数----- 能看到前半段最大值，后半段最小值 ===- 对顶堆
// Heap<int> h1, h2;
// MedianFinder() : h1{less<int>()}, h2{greater<int>()} {}

// void addNum(int num){
//     if(h1.size() == 0 || num <= h1.top()){
//         h1.push(num);
//     } else {
//         h2.push(num);
//     }
//     if( h2.size() > h1.size()){
//         h1.push(h2.pop());
//     }
//     if(h1.size() == h2.size() + 2){
//         h2.push(h1.pop());
//     }
//     return ;
// }
// double findMedian(){
//     int n = h1.size() + h2.size();
//     if( n % 2 == 1){
//         return h1.top();
//     }
//     return 1.0*(h1.top() + h2.top())/2;
// }