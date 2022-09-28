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
#include <unistd.h>
#include <time.h>
using namespace std;

bool CMP(const pair<int, int> &a, const pair<int, int> &b)
{
    return a.first < b.first;
}
int get_minimum_stop(int L, int P, vector<pair<int, int>> &stop)
{ // L -起点到终点的距离  P-起点初始的汽油量 ， stop-停靠点
    priority_queue<int> Q; //存储油量的最大堆
    int result = 0;  //记录加过几次油
    stop.push_back(make_pair(0, 0));
    sort(stop.begin(), stop.end(), CMP);
    for (int i = 0; i < stop.size(); i++)
    {  //油够，往前冲，不够找法宝，够就冲，不够就加，加不够gg
        int dis = L - stop[i].first; //当前要走的距离
        while (!Q.empty() && P < dis)
        {
            P += Q.top();
            Q.pop();
            result++;
        }
        if (Q.empty() && P < dis)
        {
            return -1;
        }
        P = P - dis;
        L = stop[i].first; //更新
        Q.push(stop[i].second); //把当前停靠点的汽油量加到最大堆
    }
    return result;
}

// 需要最小的射手数量，穿云剑
int findMinArrowShots(vector<pair<int, int>> &points)
{
    if (points.size() == 0)
    {
        return 0;
    }
    sort(points.begin(), points.end(), CMP); //左端点排序

    int shoot_num = 1;
    int shoot_begin = points[0].first;
    int shoot_end = points[0].second;

    for (int i = 1; i < points.size(); i++)
    {
        // 谁小谁nb
        if (points[i].first <= shoot_end)
        {
            shoot_begin = points[i].first;
            if (shoot_end > points[i].second)
            {
                shoot_end = points[i].second;
            }
        }
        else
        {
            shoot_num++;
            shoot_begin = points[i].first;
            shoot_end = points[i].second;
        }
    }
    return shoot_num;
}
// 从0跳到尾部最少跳跃几次
int jump(vector<int> &nums)
{
    if (nums.size() < 2)
    {
        return 0;
    }

    // pre_max---current_max之前能到达的最远内置
    // 在无法达到更远的地方时，在这之前应该跳到一个可以到的更远位置
    int current_max_index = nums[0]; //当前能到达的最远位置
    int pre_max_max_index = nums[0];
    int jump_min = 1;
    for (int i = 1; i < nums.size(); i++)
    {
        if (i > current_max_index)
        {
            jump_min++;
            current_max_index = pre_max_max_index;
        }
        if (pre_max_max_index < nums[i] + 1)
        {
            pre_max_max_index = nums[i] + 1;
        }
    }
    return jump_min;
}

bool canJump(vector<int> &nums)
{
    vector<int> index;
    for (int i = 0; i < nums.size(); i++)
    {
        index.push_back(i + nums[i]);
    }
    int jump = 0;
    int max_index = index[0];
    while (jump < index.size() && jump <= max_index)
    { // jump跳至数组尾部或jump超越了当前可以跳的最远位置
        if (max_index < index[jump])
        {
            max_index = index[jump];
        }
        jump++;
    }
    if (jump == index.size())
    {
        return true;
    }
    return false;
}
// 去掉k位数字，res->最小
string removeKdigits(string num, int k)
{
    vector<int> S;
    string result = "";
    for (int i = 0; i < num.length(); i++)
    {
        int number = num[i] - '0';
        while (S.size() != 0 && S[S.size() - 1] > number && k > 0)
        { //栈顶元素大于待选元素，谁大谁走
            S.pop_back();
            k--;
        }
        if (number != 0 || S.size() != 0)
        {
            S.push_back(number);
        }
    }
    while (S.size() != 0 && k > 0)
    {
        S.pop_back();
        k--;
    }
    for (int i = 0; i < S.size(); i++)
    {
        result.append(1, '0' + S[i]); // Append multiple characters. 参数: __n – The number of characters to append. __c – The character to use.// 返回:Reference to this string. Appends __n copies of __c to this string.
    }
    if (result == "")
    {
        result = "0";
    }
    return result;
}

int wiggleMaxLength(vector<int> &nums)
{
    if (nums.size() < 2)
    {
        return nums.size();
    }
    // 三种状态
    static const int BEGIN = 0;
    static const int UP = 1;
    static const int DOWN = 2;
    int STATE = BEGIN;
    int max_length = 1;
    // 从第二个元素开始遍历，第一个为BEGIN
    for (int i = 1; i < nums.size(); i++)
    {
        switch (STATE)
        {
        case BEGIN:
            if (nums[i - 1] < nums[i])
            {
                STATE = UP;
                max_length++;
            }
            else if (nums[i - 1] > nums[i])
            {
                STATE = DOWN;
                max_length++;
            }
            break;
        case UP:
            if (nums[i - 1] > nums[i])
            {
                STATE = DOWN;
                max_length++;
            }
            break;
        case DOWN:
            if (nums[i - 1] < nums[i])
            {
                STATE = UP;
                max_length++;
            }
            break;
        }
    }
    return max_length;
}

int findContentChildren(vector<int> &g, vector<int> &s)
{
    sort(g.begin(), g.end()); //对孩子的需求因子和糖果大小s sort
    sort(s.begin(), s.end());
    int child = 0; // child--已经满足了几个孩子，cookie尝试了几个糖果
    int cookie = 0;
    while (child < g.size() && cookie < s.size())
    {
        if (g[child] <= s[cookie])
        {
            child++;
        }
        cookie++; //每个糖果值尝试一次
    }
    return child;
}

int main()
{
    const int RMB[] = {200, 100, 20, 10, 5, 1};
    const int NUM = 6;
    int X = 628;
    int count = 0;
    for (int i = 0; i < NUM; i++)
    {
        int use = X / RMB[i];
        count += use;
        X = X - RMB[i] * use;
        printf("需要面额为%d的%d张 ", RMB[i], use);
        printf("剩余需要支付金额%d.\n", X);
    }
    printf("总共需要%d张\n", count);
    return 0;
}