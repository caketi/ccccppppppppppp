# coding:utf-8
# 反转单链表 头插-反转，尾插
# 链表空 head.next = newNode 不空 newnode.next = head.next  head.next = newNode
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None


def reverseList(head):
    if head is None:
        return head

    pHead = ListNode(-1)
    while head:
        p = head.next
        head.next = pHead.next
        pHead.next = head
        head = p
    head = pHead.next
    pHead.next = None
    del pHead
    return head

# m-n之间反转


def reverseKListInsertFront(head, m, n):
    root = ListNode(-1)
    root.next = head
    i = 0
    p = root
    # 找前驱
    while p and i < m-1:
        i += 1
        p = p.next
    t = p.next
    q = p.next
    p.next = None
    while q and i < n:
        c = q.next
        q.next = p.next
        p.next = q
        q = c
        i += 1
    t.next = c #连接已经反转的
    return root.next


def reverseKList(head, m, n):
    array = []
    p = head
    while p:
        array.append(p.val)
        p = p.next

    i = m - 1
    j = n-1
    while i < j:
        arary[i], array[j] = array[j], array[i]
        i += 1
        j -= 1

    p = head
    while p:
        v = array.pop(0)
        p.val = v
        p = p.next
    return head
