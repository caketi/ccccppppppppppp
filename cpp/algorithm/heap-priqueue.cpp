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

#include <time.h>
using namespace std;
typedef int ElemType;
struct Heap
{
    ElemType *heap;
    int len;     //堆长度
    int MaxSize; //动态数组大小
};
// init
void InitHeap(Heap &HBT)
{
    HBT.MaxSize = 10;
    HBT.heap = new ElemType[HBT.MaxSize];
    if (!HBT.heap)
    {
        cout << "no room" << endl;
        exit(1);
    }
    HBT.len = 0;
}
void ClearHeap(Heap &HBT)
{
    if (HBT.heap != NULL)
    {
        delete[] HBT.heap;
        HBT.heap = NULL;
        HBT.len = 0;
        HBT.MaxSize = 0;
    }
}
bool EmptyHeap(Heap &HBT)
{
    return HBT.len == 0;
}

void InsertHeap(Heap &HBT, ElemType item)
{
    if (HBT.len == HBT.MaxSize)
    {
        int k = sizeof(ElemType);
        HBT.heap = (ElemType *)realloc(HBT.heap, 2 * HBT.MaxSize * k);
        if (HBT.heap == NULL)
        {
            cout << "no room" << endl;
            exit(1);
        }
        HBT.MaxSize = 2 * HBT.MaxSize;
    }

    int i = HBT.len;
    while (i != 0)
    {
        int j = (i - 1) / 2;
        if (item >= HBT.heap[j])
            break;
        HBT.heap[i] = HBT.heap[j]; // 父节点下移
        i = j;                     // 当前下标从尾部往前走
    }
    // 1. i==0堆空，直接insert 2.item >= HBT.heap[j],即要插入的item比父节点da
    HBT.heap[i] = item;
    HBT.len++;
}
ElemType DeletHeap(Heap &HBT)
{
    if (HBT.len == 0)
    {
        exit(1);
    }
    ElemType temp = HBT.heap[0];
    HBT.len--;
    if (HBT.len == 0)
        return temp;
    ElemType x = HBT.heap[HBT.len]; //堆尾元素，本来9个，HBT.len-- ==8
    int i = 0; // 当前堆顶下标
    int j = 1; //当前堆顶的最小孩子
    while (j <= HBT.len - 1)
    {
        // j === 下标两个孩子最小的
        if (j < HBT.len - 1 && HBT.heap[j] > HBT.heap[j + 1])
            j++;
        if (x <= HBT.heap[j]) //堆尾元素小于等于当前左孩子（右）时停止循环，i是原堆尾元素要移动的位置
            break;
        HBT.heap[i] = HBT.heap[j]; // 让小的孩子up
        i = j;                     //更新爸爸
        j = 2 * i + 1;             // 更新孩子
    }

    HBT.heap[i] = x;
    return temp;
}
#define MAX_N 1000
int dat[MAX_N + 5], cnt = 0;
int top() { return dat[0]; }
int size() { return cnt; }

void shift_up(int ind)
{
    while (ind && dat[(ind - 1) / 2] < dat[ind])
    {
        swap(dat[(ind - 1) / 2], dat[ind]);
        ind = (ind - 1) / 2;
    }
    return;
}
void shift_down(int ind)
{
    int n = cnt - 1;
    while (ind * 2 + 1 <= n)
    {
        int temp = ind;
        if (dat[temp] < dat[ind * 2 + 1])
            temp = ind * 2 + 1;
        if (ind * 2 + 2 <= n && dat[temp] < dat[ind * 2 + 2])
            temp = ind * 2 + 2;
        if (temp == ind)
            break;
        swap(dat[temp], dat[ind]);
        ind = temp;
    }
    return;
}

void push(int x)
{
    dat[cnt++] = x;
    shift_up(cnt - 1);
    return;
}
void pop()
{
    if (size() == 0)
        return;
    swap(dat[0], dat[cnt - 1]); // 关爱小孩
    cnt -= 1;
    shift_down(0);
    return;
}
void output()
{
    cout << "heap : " << endl;
    for (int i = 0; i < cnt; i++)
    {
        printf("%d ", dat[i]);
    }
    printf("\n");
    return;
}
void output(int n)
{
    cout << "heap : " << endl;
    for (int i = 0; i < n; i++)
    {
        printf("%d ", dat[i]);
    }
    printf("\n");
    return;
}

int main()
{
    int op, val;
    int max_n = 0;
    while (cin >> op)
    {
        switch (op)
        {
        case 0:
        {
            cin >> val;
            printf("push %d to heap\n", val);
            push(val);
        }
        break;
        case 1:
        {
            printf("pop %d from heap\n", top());
            pop();
        }
        break;
        case 2:
        {
            output(max_n);
        }
        break;
        }
        max_n = max(cnt, max_n);
        output();
    }
    return 0;
}