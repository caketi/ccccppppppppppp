#include <vector>
#include <iostream>

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

class Node1
{
public:
    int val;
    Node1 *next;
    Node1 *random;

    Node1(int _val)
    {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
Node1 *copyRandomList(Node1 *head)
{
    if (head == nullptr)
        return nullptr;
    Node1 *p = head, *q, *new_head;
    while (p)
    { // copy each node ----- 1->2->3  ----  1->1->2->2->3->3
        q = new Node1(p->val);
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
    head->next = tail->next;
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