- permutation of string 
```c
void perm1(char s[], int l, int h){
    int i;
    if(l == h){
        print(s);
    }else{
        for(i = l; i <= h; i++){
            swap(s[l], s[i]);
            perm1(s, l+1, h);
            swap(s[l], s[i]);
        }
    }
}
void perm(char s[], int k){
    static int a[10] = {0};
    static char res[10];
    int i;
    if(s[k] == '\0'){
        res[k] = '\0'; print(res);
    }else{
        for(i = 0; s[i] != '\0';i++){
            if(a[i] == 0){
                res[k] = s[i];
                a[i] = 1;
                perm(s, k+1);
                a[i] = 0;
            }
        }
    }
}
```