class UnionSet
{
private:
    /* data */
public:
    int *color, n;
    UnionSet(int n) : n(n)
    {
        color = new int[n + 1];
        for (int i = 0; i <= n; i++)
        {
            color[i] = i;
        }
    }

    int find(int x)
    {
        return color[x];
    }

    void merge(int a, int b)
    {
        if (color[a] == color[b])
            return;
        int cb = color[b];
        for (int i = 0; i <= n; i++)
        {
            if (color[i] == cb)
                color[i] = color[a];
        }
        return;
    }
};
