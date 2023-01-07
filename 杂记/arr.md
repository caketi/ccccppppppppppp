- polynomial representation
```c
struct Tm{
    int co;
    int exp;
}
struct Poly{
    int n;
    struct Tm *t;
}
struct Poly p;
scanf("%d", &p.n);
p.t = new Tm[p.n];
for(i = 0; i < p.n ; i++){
    printf("Tm no %d", i+1);
    scanf("%d%d", &p.t[i].co,&p.t[i].exp);
}
```
- array repre sparse matrix
```c
struct Element{
    int i;
    int j;
    int x;
};
struct Sparse{
 int m;
 int n;
 int num;
 struct Element *e;
};
void create(struct Sparse *s){
    int i;
    printf("Enter Dimensions");
    scanf("%d%d", &s->m, &s->n);
    printf("Enter no of non-zero");
    scanf("%d", &s->num);
    s->e = new ELements[s->num];
    printf("Enter all elements");
    for(i = 0; i < s->num; i++){
        scanf("%d%d%d", &s->e[i].i, &s->e[i].j, &s->e[i].x);
    }
}
```