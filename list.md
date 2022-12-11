


- insert first in doubly list

```c
Node *t = new Node;
t->data = x;
t->prev = NULL;
t->next = first;
first->prev = t;
first = t;
```

- insert given index in doubly list

```c
Node *t = new Node;
t->data = x;
for(int i = 0; i < pos -1; i++){
    p = p ->next;
}
t->next = p->next;
t->prev = p;
if(p->next){
    p->next->prev = t;
}
p->next = t;
```

- delete first in doubly list

```c
p = first;
first = first->next;
x = p->data;
delete p;
if(first) first->prev = NULL;
```

- delete given index in doubly list

```c
p = first;
for(int i = 0; i < pos -1; i++){
    p = p -> next;
}
p->prev->next = p->next;
if(p->next){
    p->next->prev = p->prev;
}
x = p->data;
delete p;

```

- delete from linked list

```c
int delete(int pos){
    Node *p, *q;
    int x = -1, i;
    if(pos == 1){
        x = first->data;
        p = first;
        first = first->next;
        delete p;
    }
    else {
        p = first;
        q = NULL;
        for(i = 0; i < pos-1 && p; i++){
                q=p;
                p=p->next;
        }
        if(p){
            q->next=p->next;
            x= p->next;
        }
        delete p;
    }
    return x;
}
```

- check loop in list


```c
int isLoop(Node *f){
    Node *p, *q;
    p = q = f;
    do{
        p=p->next;
        q=q->next;
        q=q!=NULL?q->next:NULL;
    }while(p&&q);
    return p == q ? true:false;
}
```
```java
public static class Node{
    public int value;
    public Node next;

    public Node(int data){
        this.value = data;
    }
}

public static Node getIntersectNode(Node head1, Node head2){
    if(head1==null || head2==null){
        return null;
    }
    Node loop1=getLoopNode(head1);
    Ndoe loop2=getLoopNode(head2);
    if(loop1==null&&loop2==null){
        return noLoop(head1, head2);
    }
    if(loop1!=null&&loop2!=null){
        return bothLoop(head1, loop1, head2, loop2);
    }
}

public static Node noLoop(Node head1, Node head2){
    if(head1==null || head2==null){
        return null;
    }
    Node cur1=head1;
    Node cur2=head2;
    int n = 0;
    while(cur1.next!=null){
        n++;
        cur1=cur1.next;
    }
    while(cur2.next!=null){
        n--;
        cur2=cur2.next;
    }
    if(cur1!=cur2){
        return null;
    }
    // n : cur1.len-cur2.len
    cur1 = n > 0 ? head1 : head2;//谁长，谁的头变成cur1
    cur2 = cur1 == head1 ? head2 : head1;// 短
    n = Math.abs(n);
    while(n!=0){
        n--;
        cur1=cur1.next;
    }
    while(cur1!=cur2){
        cur1=cur1.next;
        cur2=cur2.next;
    }
    return cur1;
}
// 两个有环链表，返回第一个相交节点
public static Node bothLoop(Node head1, Node loop1, Node head2, Node loop2){
    Node cur1 = null;
    Node cur2 = null;
    if(loop1 == loop2){
        cur1=head1;
        cur2=head2;
        int n = 0;
        while(cur1!=loop1){
            n++;
            cur1=cur1.next;
        }
        while(cur2!=loop2){
            n--;
            cur2=cur2.next;
        }
        cur1=n>0?head1:head2;
        cur2=cur1==head1 ? head2 : head1;
        n = Math.abs(n);
        while(n != 0){
            n--;
            cur1=cur1.next;
        }
        while(cur1!=cur2)[
            cur1=cur1.next;
            cur2=cur2.next;
        ]
        return cur1;
    }else{
        cur1=loop1.next;
        while(cur1!=loop1){
            if(cur1==loop2){
                return loop1;
            }
            cur1=cur1.next;
        }
        return null;
    }
}

public static Node getLoopNode(Node head){
    if(head == null || head.next == null || head.next.next == null){
        return null;
    }
    Node slow = head.next;
    Node fast = head.next.next;
    while(slow != fast){
        if(fast.next == null || fast.next.next == null){
            return null;
        }
        fast = fast.next.next;
        slow = slow.next;
    }
    fast = head;
    while(slow != fast){
        slow = slow.next;
        fast = fast.next;
    }
    return slow;
}
```
- concatenating 2 linked list

```c
p = first;
while(p->next != NULL){
    p = p->next;
}
p->next = second;
second = NULL;
```

- reversing a linked list

```c
p = first;
i = 0;
while(p != NULL){
    a[i] = p -> data;
    p = p->next;
    i++;
}
p = first; i--;
while(p!= NULL){
    p->data = a[i--];
    p=p->next;
}
```

- maximum elements in a linked list

```c
int max1(Node *p){
    int m = -33333; MIN_INT;
    while(p){
        if(p->data > m){
            m = p->data;
        }
        p = p->next;
    }
    return m;
}
int  max(Node *p){
    int x = 0;
    if(p == 0){
        return MIN_INT;
    }else{
        x = max(p->next);
        if(x > p->data){
            return x;
        }else{
            return p->data;
        }
    }
}
```

- counting nodes in a linked list

```C
int count(struct Node *p){
    int x = 0;
    if(p){
        x = count(p->next);
        return x + 1;
    }else {
        return x;
    }
}
```

- find intersection of 2 linked list

```c
p = first;
while(p) push(&stk1, p);
p = second;
while(p) push(&stk2, p);
while(stackTop(stk1) == stackTop(stk2)){
    p = pop(&stk1); pop(&stk2);
}
printf("%d", p->data);
```

- find middle node of a linked list

```c
p = q = first;
while(q){
    q = q->next;
    if(q) q = q->next;
    if(q) p = p->next;
}
printf("%d", p->data);
```
- sparse matrix using linked list
```c
struct Node{
    int col;
    int val;
    struct Node *next;
};
for(i = 0; i < m; i++){
    p = a[i];
    for(j = 0; j < n; j++){
        if(j == p->col){
            printf("%d", p->val);
            p = p->next;
        }else {
            printf("o");
        }
    }
}
```