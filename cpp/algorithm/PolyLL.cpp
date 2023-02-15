#include <stdio.h>
#include <iostream>
#include <cmath>
struct Node{
    int coeff;
    int exp;
    struct Node *next;
}*poly = NULL;

void create(){
    struct Node *t;
    struct Node *last;
    int num, i;
    printf("Enter number of terms: ");
    scanf("%d", &num);
    printf("Enter each term with coeff and exp\n");
    for(i = 0; i <num; i++){
        t = (struct Node *)malloc(sizeof(struct Node));
        scanf("%d%d", &t->coeff, &t->exp);
        t->next = NULL;
        if(poly == NULL){
            poly = last = t;
        }else{
            last->next = t;
            last = t;
        }
    }
}
void Display(struct Node *p){
    while(p){
        printf("%dx%d + ", p->coeff, p->exp);
        p=p->next;
    }
    printf("\n");
}
int Eval(struct Node *p, int x){
    int val = 0;
    while(p){
        val += p->coeff*pow(x,p->exp); // 没看明白
        p=p->next;
    }
    return val;
}
int main(){
    create();
    Display(poly);
    printf("%d\n", Eval(poly,1 ));
}