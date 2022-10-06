class UnionSet
{
private:
    /* data */
public:
    int *boss, n;
    UnionSet(int n) : n(n)
    {
       boss = new int[n+1];
       for(int i = 0; i<=n; i++){
        boss[i] = i;
       }
    }

    int find(int x)
    {   
        if(boss[x] == x) return x;
        return find(boss[x]);
    }

    void merge(int a, int b)
    {
        int fa = find(a), fb = find(b);
        if(fa == fb) return;
        boss[fa] = fb;
        return;
    }
};




