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
// 虚头--链表头地址可能改变

using namespace std;

int data2[100];
int next2[100];

struct Node
{
    Node() : data(0), next(nullptr) {}
    Node(int data) : data(data), next(nullptr) {}
    Node(int data, Node *next) : data(data), next(next) {}
    int data;
    Node *next;
};

class RandomListNode
{
public:
    int val;
    RandomListNode *next;
    RandomListNode *random;

    RandomListNode(int _val)
    {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
RandomListNode *copyRandomList(RandomListNode *head)
{
    if (head == nullptr)
        return nullptr;
    RandomListNode *p = head, *q, *new_head;
    while (p)
    { // copy each node ----- 1->2->3  ----  1->1->2->2->3->3
        q = new RandomListNode(p->val);
        q->random = p->random;
        q->next = p->next;
        p->next = q;
        p = q->next;
    }
    p = head->next; // 第一个被复制出的node
    while (p)
    { //
        if (p->random)
            p->random = p->random->next;
        (p = p->next) && (p = p->next); // p = p->next->next;先试探
    }
    new_head = head->next;
    p = head;
    while (p)
    {
        q = p->next;
        p->next = q->next;
        if (p->next)
            q->next = p->next->next;
        p = p->next;
    }
    return new_head;
}
RandomListNode *copyRandomList_v2(RandomListNode *head)
{
    map<RandomListNode *, int> node_map; //地址->节点位置的映射
    vector<RandomListNode *> node_vec;   //根据存储节点位置访问地址
    RandomListNode *ptr = head;
    int i = 0;
    while (ptr)
    {
        node_vec.push_back(new RandomListNode(ptr->val));
        node_map[ptr] = i; //记录原始链表地址->节点编号的node_map
        ptr = ptr->next;
        i++;
    }
    node_vec.push_back(0);
    ptr = head;
    i = 0;
    while (ptr)
    {
        node_vec[i]->next = node_vec[i + 1]; //连接新链表next指针
        if (ptr->random)
        { // node_map确认地址->节点的编号（原链表random指针指向的位置）
            int id = node_map[ptr->random];
            node_vec[i]->random = node_vec[id]; // 连接新链表的random指针
        }
        ptr = ptr->next;
        i++;
    }
    return node_vec[0];
}
// 分隔链表--86leetcode--一个区域小于x一个大于等于
// r1->.....->p1
// r2-> ....->p2
Node *partition(Node *head, int x)
{
    Node r1, r2, *p1 = &r1, *p2 = &r2, *p = head, *q; // p1->r1 p2->r2
    while (p)
    {
        q = p->next; //保存下一个位置
        if (p->data < x)
        {
            p->next = p1->next; // r1->p
            p1->next = p;       // p1->p
            p1 = p;             // 保证p1是头部
        }
        else
        {
            p->next = p2->next; // r2->p2
            p2->next = p;
            p2 = p;
        }
        p = q; // 下一个节点
    }
    p1->next = r2.next;
    return p1->next;
}

// recursive
Node *reverseList2(Node *head)
{
    if (head == nullptr || head->next == nullptr)
        return head;
    Node *tail = head->next;
    Node *p = reverseList2(head->next);
    head->next = tail->next; //想想就两个节点head tail
    tail->next = head;
    return p;
}
Node *reverseList3(Node *head, int n)
{
    if (n == 1)
        return head;
    Node *tail = head->next;
    Node *p = reverseList3(head->next, n - 1);
    head->next = tail->next;
    tail->next = head;
    return p;
}
Node *reverseBetween(Node *head, int m, int n)
{
    Node *ret = new Node(0, head); // 虚拟头结点
    Node *p = ret;                 // 虚拟头结点
    int cnt = n - m + 1;
    while (--m)
        p = p->next; // m = 2 loops 1
    p->next = reverseList3(p->next, cnt);
    return ret->next;
}
// Non-recursive
Node *reverseList(Node *head)
{
    if (head == nullptr || head->next)
        return head;
    Node *pre = nullptr; // 反转头
    Node *cur = head;    // 未反转的头
    Node *p = head->next;
    while (cur)
    {
        cur->next = pre;
        pre = cur;
        (cur = p) && (p = p->next);
    }
    return pre;
}
Node *rotateRight(Node *head, int k)
{
    if (head == nullptr)
        return nullptr;
    int n = 1;
    Node *p = head;
    while (p->next)
    {
        p = p->next;
        n += 1;
    }
    p->next = head; // 把链表连起来，变环
    k %= n;         // 去掉多余的整圈移动
    k = n - k;
    while (k--)
        p = p->next; // k =2 执行两次
    head = p->next;  // 指到下一个
    p->next = nullptr;
    return head;
}
Node *removeNthFromEnd(Node *head, int n)
{
    Node *ret = new Node(0, head);
    Node *p = ret;
    Node *q = head;
    while (n--)
        q = q->next; // p和q相差n 也就是倒数的个数
    while (q)
    {
        p = p->next;
        q = q->next;
    }
    p->next = p->next->next;
    return ret->next;
}
// 前提---有序
Node *deleteDuplicates(Node *head)
{
    if (head == nullptr)
        return nullptr;
    Node *p = head;
    while (p->next)
    {
        if (p->data == p->next->data)
        {
            p->next = p->next->next;
        }
        else
        {
            p = p->next;
        }
    }
    return head;
    //只要出现重复都删了
    // Node* ret = new Node(0, head);
    // Node* p = ret;
    // Node *q = nullptr;
    // while(p->next){
    //     if(p->next->next && p->next->val == p->next->next->val){
    //         q = p->next->next;
    //         while(q && q->val == p->next->val) q = q->next;
    //         p->next = q;
    //     } else{
    //         p = p->next;
    //     }
    // }
    // return ret->next;
}

int getNext(int x)
{
    int z = 0;
    while (x)
    {
        z += (x % 10) * (x % 10);
        x /= 10;
    }
    return z;
}
bool isHappyNumber(int n)
{
    int p = n, q = n;
    do
    {
        p = getNext(p);
        q = getNext(getNext(q));
    } while (p != q && q != 1);
    return q == 1;
}

Node *partition(Node *head, int x)
{
    Node less_head(0);
    Node more_head(0); //两个临时头结点
    Node *less_ptr = &less_head;
    Node *more_ptr = &more_head;
    while (head)
    {
        if (head->data < x)
        {
            less_ptr->next = head;
            less_ptr = head; //链接完成后，less_ptr向后移动，指向head
        }
        else
        {
            more_ptr->next = head;
            more_ptr = head;
        }
        head = head->next;
    }
    less_ptr->next = more_head.next;
    more_ptr->next = NULL;
    return less_head.next; //返回less_head的next节点
}

// nums = {1,3,4,2,2}
int findDuplicate(vector<int>& nums){
    int p = 0, q = 0;
    do{
        p = nums[p];
        q = nums[nums[q]];
    } while(p != q);
    p = 0; //meet here , go together
    while(p != q){
        p = nums[p];
        q = nums[q];
    }
    return p;
}
Node *detectCycle_v2(Node *head)
{
    set<Node *> node_set;
    while (head)
    {
        if (node_set.find(head) != node_set.end())
        {
            return head; //返回环位置
        }
        node_set.insert(head);
        head = head->next;
    }
    return NULL;
}
Node *detectCycle_fastslowptr_v2(Node *head)
{
    Node *fast = head;
    Node *slow = head;
    Node *meet = NULL;
    while (fast)
    {
        slow = slow->next;
        fast = fast->next;
        if (!fast)
        { // fast遇到链表尾，返回NULL
            return NULL;
        }
        fast = fast->next;
        if (fast == slow) // fast与slow相遇，记录相遇位置
        {
            meet = fast;
            break;
        }
    }
    if (meet == NULL) //没有相遇，证明无环
    {
        return NULL;
    }
    while (head && meet)
    {
        if (head == meet) // head与meet相遇，遇到环的起始位置
        {
            return head;
        }

        head = head->next; // head与meet每次走一步
        meet = meet->next;
    }
}
Node *detectCycle(Node *head)
{
    if (head == nullptr)
        return nullptr;
    Node *p = head;
    Node *q = head->next;
    while (p != q && q && q->next)
    {
        p = p->next;
        q = q->next->next;
    }
    if (q == nullptr || q->next == nullptr)
        return nullptr; // q快-判断q
    // p = head->next;
    // q = head->next->next;
    // while( p != q){
    //     p = p->next;
    //     q = q->next->next;
    // }
    p = q = head;
    do
    {
        p = p->next;
        q = q->next;
    } while (p != q); // 注意判断条件，dowhile先执行一步
    p = head;         // 把p拉回头部，再次遍历直到p和q相遇
    while (p != q)
    {
        p = p->next;
        q = q->next->next;
    }
    return q;
}

bool hasCycle(Node *head)
{
    if (head == nullptr)
        return false;
    Node *p = head;       // slow ptr
    Node *q = head->next; // fast ptr
    while (p != q && q && q->next)
    {
        p = p->next;
        q = q->next->next;
    }
    return q && q->next;
}

void add(int ind, int p, int val)
{
    next2[ind] = p;
    data2[p] = val;
    return;
}

void _test_prefixOrpostfix()
{
    int m = 3;
    int n = 3;
    printf("prefix--/++: ");
    while (--m)
    {
        printf("a");
    }
    printf("\n");
    printf("postfix--/++: ");
    while (n--)
    {
        printf("b");
    }
    printf("\n");
}

int main()
{
    _test_prefixOrpostfix();

    int head2 = 3;
    data2[3] = 0;
    add(3, 5, 1);
    add(5, 2, 2);
    add(2, 7, 3);
    add(7, 9, 100);
    int p2 = head2;
    while (p2 != 0)
    {
        printf("%d->", data2[p2]);
        p2 = next2[p2];
    }
    printf("\n");

    Node *head = NULL;
    head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(44);
    Node *p = head;
    while (p != NULL)
    {
        printf("%d->", p->data);
        p = p->next;
    }

    // printf("\nreversedList1-nonrecursive:  ");
    // Node* reversedList1 = reverseList(head);
    // while(reversedList1 != NULL) {
    //     printf("%d->", reversedList1->data);
    //     reversedList1 = reversedList1->next;
    // }
    // printf("\nreversedList2-recursive:  ");
    // Node* reversedList2 = reverseList2(head);
    // while(reversedList2 != NULL) {
    //     printf("%d->", reversedList2->data);
    //     reversedList2 = reversedList2->next;
    // }
    // printf("\nreversedList3-recursive:  ");
    // Node* reversedList3 = reverseList3(head,3);
    // while(reversedList3 != NULL) {
    //     printf("%d->", reversedList3->data);
    //     reversedList3 = reversedList3->next;
    // }
    // printf("\n rotateRight:  ");
    // Node* rotateRightList = rotateRight(head,2);
    // while(rotateRightList != NULL) {
    //     printf("%d->", rotateRightList->data);
    //     rotateRightList = rotateRightList->next;
    // }
    printf("\n removeNodeNthFromEnd:  ");
    Node *removeNthFromEnd1 = removeNthFromEnd(head, 2);
    while (removeNthFromEnd1 != NULL)
    {
        printf("%d->", removeNthFromEnd1->data);
        removeNthFromEnd1 = removeNthFromEnd1->next;
    }
    printf("\n");
    bool hasCycle2 = hasCycle(head);
    Node *detectCycle2 = detectCycle(head);
    printf("\n NoCycle is 0, hasCycle is 1!\n The value is: %d  detect: %d \n", hasCycle2, detectCycle2);
    return 0;
}

class randomAccessNode
{
    int n;
    Node *head;
    randomAccessNode(Node *head) : head(head), n(0)
    {
        Node *p = head, *q;
        while (p)
            q = p, p = p->next, n += 1;
        q->next = head; // 连成环
    }
    int getRandom()
    {
        int x = rand() % n;
        while (x--)
            head = head->next;
        return head->data;
    }
};

//
class palindromeList
{
    Node *reverse(Node *head)
    {
        Node ret, *p = head, *q;
        while (p)
        {
            q = p->next;
            p->next = ret.next;
            p = q;
        }
        return ret.next;
    }
    bool isPalindrome(Node *head)
    {
        if (head == nullptr)
            return false;
        Node *p = head, *q = head;
        while (q->next && q->next->next)
        {
            p = p->next;
            q = q->next->next;
        }
        p->next = reverse(p->next);
        q = p->next;
        p = head;
        while (q)
        {
            if (p->data != q->data)
                return false;
            p = p->next;
            q = q->next;
        }
        return true;
    }
};

Node *reverseBetween_1(Node *head, int m, int n)
{
    int change_len = n - m + 1; //计算需要翻转的节点个数
    Node *pre_head = NULL;      //初始化开始翻转的节点的前驱
    Node *result = head;        //最终结果的链表的头结点，非特殊情况即为head
    while (head && --m)
    {                    //走m-1步
        pre_head = head; //记录head的前驱
        head = head->next;
    }
    Node *modify_list_tail = head;

    Node *new_head = NULL;
    while (head && change_len)
    {
        Node *next = head->next;
        head->next = new_head;
        new_head = head;
        head = next;
        change_len--;
    }
    modify_list_tail->next = head;
    if (pre_head)
    { //如果pre_head不空，说明不是从第一个节点开始翻转， m>1
        pre_head->next = new_head;
    }
    else
    {
        result = new_head;
    }
    return result;
}

int get_list_length(Node *head)
{
    int len = 0;
    while (head)
    {
        len++;
        head = head->next;
    }
    return len;
}
Node *forward_long_list(int long_len, int short_len, Node *head)
{
    int delta = long_len - short_len;
    while (head && delta)
    {
        head = head->next;
        delta--;
    }
    return head;
}
Node *getIntersectionNode_v2(Node *headA, Node *headB)
{
    int list_A_len = get_list_length(headA);
    int list_B_len = get_list_length(headB);
    if (list_A_len > list_B_len)
    { // 长链表移动head到和短链表的head一致
        headA = forward_long_list(list_A_len, list_B_len, headA);
    }
    else
    {
        headB = forward_long_list(list_B_len, list_A_len, headB);
    }
    while (headA && headB)
    {
        if (headA == headB)
        {
            return headA;
        }
        headA = headA->next;
        headB = headB->next;
    }
    return NULL;
}
Node *getIntersectionNode(Node *headA, Node *headB)
{
    set<Node *> node_set;
    while (headA)
    {
        node_set.insert(headA);
        headA = headA->next;
    }
    while (headB)
    {
        if (node_set.find(headB) != node_set.end())
        {
            return headB;
        }
        headB = headB->next;
    }
    return NULL;
}
// 合并两个已排序的链表
Node *mergeTwoLists(Node *l1, Node *l2)
{
    Node temp_head(0);
    Node *pre = &temp_head;
    while (l1 && l2)
    {
        if (l1->data < l2->data)
        {
            pre->next = l1;
            l1 = l1->next;
        }
        else
        {
            pre->next = l2;
            l2 = l2->next;
        }
        pre = pre->next;
    }
    if (l1)
    {
        pre->next = l1;
    }
    if (l2)
    {
        pre->next = l2;
    }
    return temp_head.next;
}
bool cmp(const Node *a, const Node *b)
{
    return a->data < b->data;
}
Node *mergeKLists(vector<Node *> &lists)
{
    vector<Node *> node_vec;
    for (int i = 0; i < lists.size(); i++)
    {
        Node *head = lists[i];
        while (head)
        {
            node_vec.push_back(head);
            head = head->next;
        }
    }
    if (node_vec.size() == 0)
    {
        return NULL;
    }
    sort(node_vec.begin(), node_vec.end(), cmp);
    for (int i = 1; i < node_vec.size(); i++)
    {
        node_vec[i - 1]->next = node_vec[i];
    }
    node_vec[node_vec.size() - 1]->next = NULL;
    return node_vec[0];
}
Node *mergeKLists_v2(vector<Node *> &lists)
{
    if (lists.size() == 0)
    {
        return NULL;
    }
    if (lists.size() == 1)
    {
        return lists[0];
    }
    if (lists.size() == 2)
    {
        return mergeTwoLists(lists[0], lists[1]);
    }
    int mid = lists.size() / 2;
    vector<Node *> sub1_lists;
    vector<Node *> sub2_lists;
    for (int i = 0; i < mid; i++)
    {
        sub1_lists.push_back(lists[i]);
    }
    for (int i = mid; i < lists.size(); i++)
    {
        sub2_lists.push_back(lists[i]);
    }
    Node *l1 = mergeKLists_v2(sub1_lists);
    Node *l2 = mergeKLists_v2(sub2_lists);
    return mergeTwoLists(l1, l2);
}