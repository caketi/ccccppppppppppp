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
#include <vector>
#include <unordered_map>
#include <assert.h>
using namespace std;

#define low16(a) ((a) & 0xffff)
#define high16(a) (((a) & 0xffff0000) >> 16)
void radix_sort(int *arr, int n){
    int cnt[65536] = {0};
    int *temp = (int *) malloc(sizeof(int) *n);
    // low 16 bit sort
    for(int i = 0; i <n ;i ++) cnt[low16(arr[i])] += 1; //count
    for(int i = 1; i<65536; i++) cnt[i] += cnt[i-1]; //prefix sum
    for(int i = n-1; i>=0; --i) temp[--cnt[low16(arr[i])]] = arr[i]; // placement

    //init cnt
    for(int i = 0; i< 65536; i++) cnt[i] = 0;

    // high 16 bit sort
    for(int i = 0; i< n; i++) cnt[high16(temp[i])] += 1;
    for(int i = 1; i < 65536; i ++) cnt[i] += cnt[i-1];
    for(int i = n-1; i>=0;--i) arr[--cnt[high16(temp[i])]] = temp[i];
    free(temp);
    return;
}

void output(int *arr, int n){
    for(int i = 0; i<n; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
    return ;
}
int *getRandData(int n){
    int *temp = (int *)malloc(sizeof(int) * n);
    for(int i = 0; i<n;i++) temp[i] = rand();
    return temp;
}
int main(){
    #define MAX_N 20
    int *arr = getRandData(MAX_N);
    output(arr, MAX_N);
    radix_sort(arr, MAX_N);
    output(arr, MAX_N);
    free(arr);
    return 0;
}

// arr1= [2,3,1,3,2,4,6,7,9,2,19] 
// arr2 = [2,1,4,3,9,6]
// [2,2,2,1,4,3,3,9,6,7,19]
vector<int> relativeSortArray(vector<int> &arr1, vector<int> &arr2){
    int cnt[1005] = {0};
    for(auto x: arr1) cnt[x] += 1;
    int k = 0;
    for(auto x : arr2) while(cnt[x]--) arr1[k++] = x;
    for(int i = 0; i< 1001; i++){
        if(cnt[i] <= 0) continue;
        while(cnt[i] --) arr1[k++] = i;
    }
    return arr1;
}

// [3,6,9,1] ----- [1,3,6,9] 相邻最大差距值
//  3

int maximumGap(vector<int>& nums){
    int cnt[65536] = {0};
    vector<int> temp(nums.size());
    for(auto x : nums) cnt[x & 0xffff] += 1;
    for(int i = 1; i < 65536; i++) cnt[i] += cnt[i-1];
    for(int i = nums.size() -1; i>=0; --i) temp[--cnt[nums[i] % 65536]] = nums[i];
    memset(cnt, 0, sizeof(cnt));
    for(auto x : temp)  cnt[x/65536] += 1;
    for(int i = temp.size() -1; i >= 0; --i) nums[--cnt[temp[i] / 65536]] = temp[i];
    int ans = 0;
    for(int i = 1; i< nums.size(); i++){
        ans = max(ans, nums[i] - nums[i-1]);
    }
    return ans;
}

//  citations = [ 3, 0 ,6, 1,5]
//  01356
//  3
int hIndex(vector<int> & citations){
    sort(citations.begin(), citations.end());
    int h = 1, n = citations.size();
    while( h<=n && citations[n-h] >= h)  ++h;
    return h-1;
}

// 课程依赖
// 5   1->3->4->1 有环
// [[1,0], [1,2], [3,1], [1,4], [4,3]]
//  false
bool canFinish(int numCourses, vector<vector<int>> &prerequisites){
    int indeg[numCourses];  // 入度
    memset(indeg, 0, sizeof(indeg));
    vector<vector<int>> g(numCourses); // 点指向其他点集合
    queue<int> q; // 入度0
    for(auto x: prerequisites){
        indeg[x[0]] += 1;
        g[x[1]].push_back(x[0]); // x1-->x0
    }
    for(int i = 0; i<numCourses; i++){
        if(indeg[i] == 0) q.push(i); // 入度0 加入 q
    }
    int cnt = 0;
    // vector<int> ans;
    while(!q.empty()){
        int ind = q.front();
        q.pop();
        cnt+=1; // 过不去的节点
        // ans.push_back(ind);
        cout << "pop : " << ind << endl;
        for(auto to: g[ind]){
            indeg[to] -= 1;
            if(indeg[to] == 0) q.push(to);
        }
    }
    return cnt == numCourses;
    // if(ans.size() == numCourses) return ans;
    //  return 
}
// 合并区间
vector<vector<int>> merge(vector<vector<int>> & intervals){
    vector<vector<int>> arr;
    vector<int> temp(2); // [1, 2] 1 -1 左右括号 区间
    for( auto x: intervals){
        temp[0] = x[0];
        temp[1] = 1;
        arr.push_back(temp);
        temp[0] = x[1];
        temp[1] = -1;
        arr.push_back(temp);
    }
    sort(arr.begin(), arr.end(),
    [](const vector<int> &a, const vector<int> &b)->bool{
        if(a[0] - b[0]) return a[0] < b[0]; // small -> big
        return a[1] > b[1]; // 1 -1 1 -1 ---   1 1 -1 -1 
    }
    );
    int pre = -1, sum = 0;
    vector<vector<int>> ret;
    for(int i = 0; i< arr.size(); i++){
        if(pre == -1) pre = arr[i][0];
        sum += arr[i][1];
        if(sum == 0){
            temp[0] = pre;
            temp[1] = arr[i][0];
            ret.push_back(temp);
            pre = -1;
        }
    }
    return ret;
}
struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x): val(x), left(NULL), right(NULL){}
};

int getPathSum(TreeNode* root, int sum){
    if(root == NULL) return 0;
    int val = sum - root->val;
    return (root->val == sum) + getPathSum(root->left, val) + getPathSum(root->right, val);
}


int pathSum(TreeNode* root , int sum){
    if(root == NULL) return 0;
    int a = getPathSum(root, sum);
    return a + pathSum(root->left, sum) + pathSum(root->right, sum);
}
// 删除被覆盖区间 [[1,4] , [3,6], [2,8]]  2 [2,8] 被删除
//  不下降子序列 长度至少2
// [4,6,7,7] [4,6] 47 467 4677 67 677 77 477
// k -- 从哪里开始选数字 buff--k之前存了哪些
void getResult(vector<int> &nums, int k, vector<int> buff, vector<vector<int>> &ret){
    if(buff.size()) ret.push_back(buff);
    buff.push_back(0);
    unordered_map<int, int> can;
    for(int i = k; i<nums.size(); i++){
        if(can.find(nums[i]) != can.end()) continue;
        if(buff.size() == 1 ||  nums[i] >= buff[buff.size() -2]){
            buff[buff.size()-1] = nums[i];
            can[nums[i]] = 1;
            getResult(nums, i+1, buff, ret);
        }
    }
    return;
}
vector<vector<int>> findSubsequeneces(vector<int>& nums){
    vector<vector<int>> ret;
    getResult(nums, 0, vector<int>(), ret);
    return ret;
}