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