#include <iostream>
#include <cstdlib>
#include <queue>
#include <stack>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <vector>
using namespace std;

class Queue
{
public:
    Queue(int n) : arr(n), head(0), tail(0), cnt(0) {}
    void push(int x)
    {
        if (full())
        {
            cout << "queue full!" << endl;
            return;
        }
        arr[tail] = x;
        tail += 1;
        cnt += 1;
        if (tail == arr.size())
            tail = 0;
        return;
    }
    void push_front(int x)
    {
        if (full())
        {
            cout << "queue full" << endl;
            return;
        }

        head = head - 1;
        if (head == -1)
            head = arr.size() - 1;
        arr[head] = x;
        cnt += 1;
        return;
    }
    int pop_end()
    {
        if (empty())
            return -1;
        tail = (tail - 1 + arr.size()) % arr.size();
        cnt -= 1;
        return 0;
    }
    int pop()
    {
        if (empty())
            return -1;
        head += 1; // head = (head+1)%arr.size();
        cnt -= 1;
        if (head == arr.size())
            head = 0;
        return 0;
    }
    bool empty()
    {
        return cnt == 0;
    }
    int front()
    {
        if (empty())
            return 0;
        return arr[head];
    }
    int rear()
    {
        if (empty())
            return -1;
        return arr[(tail - 1 + arr.size()) % arr.size()];
    }
    bool full()
    {
        return cnt == arr.size();
    }
    int size()
    {
        return cnt;
    }
    void clear()
    {
        head = tail = cnt = 0;
        return;
    }
    void output()
    {
        cout << "Queue : ";
        for (int i = 0, j = head; i < cnt; i++)
        {
            cout << arr[j] << " ";
            j += 1;
            if (j == arr.size())
                j = 0;
        }
        cout << endl;
        return;
    }

private:
    int head, tail;
    int cnt;
    vector<int> arr;
};

int main()
{
    string op;
    int value;
    Queue q(5);
    while (cin >> op)
    {
        if (op == "i") // insert
        {
            cin >> value;
            q.push(value);
        } else if (op == "if"){
            cin >> value;
            q.push_front(value);
        }
        else if (op == "f") // front
        {
            cout << "front element : " << q.front() << endl;
        }
        else if (op == "p") // pop
        {
            q.pop();
        }
        else if (op == "s") // size
        {
            cout << "queue size : " << q.size() << endl;
        }
        else if (op == "c") // clear
        {
            cout << "queue cleared!!!" << endl;
            q.clear();
        }
        else if (op == "q")
        {
            cout << "Quit,byeee!";
            exit(0);
        }
        else if (op == "r")
        {
            cout << "rear element: " << q.rear() << endl;
        }
        else if (op == "pe")
        {
            q.pop_end();
        }
        q.output();
    }
    return 0;
}