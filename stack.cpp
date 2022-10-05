#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <stack>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <time.h>
using namespace std;
void compute(stack<int> &number_stack, stack<char> &operation_stack)
{
    if (number_stack.size() < 2)
    {
        return;
    }
    int num2 = number_stack.top();
    number_stack.pop();
    int num1 = number_stack.top();
    number_stack.pop();
    if (operation_stack.top() == '+')
    {
        number_stack.push(num1 + num2);
    }
    else if (operation_stack.top() == '-')
    {
        number_stack.push(num1 - num2);
    }
    operation_stack.pop();
}
int caclculate(string s)
{
    static const int STATE_BEGIN = 0;
    static const int NUMBER_STATE = 1;
    static const int OPERATION_STATE = 2;
    stack<int> nubmer_stack;
    stack<char> operation_stack;

    int number = 0;
    int STATE = STATE_BEGIN;
    int compute_flag = 0;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == ' ')
        {
            continue;
        }
        switch (STATE)
        {
        case STATE_BEGIN:
            if (s[i] >= '0' && s[i] <= '9')
            {
                STATE = NUMBER_STATE;
            }
            else
            {
                STATE = OPERATION_STATE;
            }
            i--;
            break;
        case NUMBER_STATE:
            if (s[i] >= '0' && s[i] <= '9')
            {
                number = number * 10 + s[i] - '0';
            }
            else
            {
                nubmer_stack.push(number);
                if (compute_flag == 1)
                {
                    compute(nubmer_stack, operation_stack);
                }
                number = 0;
                i--;
                STATE = OPERATION_STATE;
            }
            break;
        case OPERATION_STATE:
            if (s[i] == '+' || s[i] == '-')
            {
                operation_stack.push(s[i]);
                compute_flag = 1;
            }
            else if (s[i] == '(')
            {
                STATE = NUMBER_STATE;
                compute_flag = 0;
            }
            else if (s[i] >= '0' && s[i] <= '9')
            {
                STATE = NUMBER_STATE;
                i--;
            }
            else if (s[i] == ')')
            {
                compute(nubmer_stack, operation_stack);
            }
            break;
        }
    }
}


bool checkIsValidOrder(queue<int> &order)
{
    stack<int> s;
    int n = order.size();
    for (int i = 1; i <= n; i++)
    {
        s.push(i);
        while (!s.empty() && order.front() == s.top())
        {
            s.pop();
            order.pop();
        }
    }
    if (!s.empty())
    {
        return false;
    }
    return true;
}

class MinStack
{
public:
    void push(int x)
    {
        _data.push(x);
        if (!_min.empty())
        {
            _min.push(x);
        }
        else
        {
            if (x > _min.top())
            {
                x = _min.top();
            }
            _min.push(x);
        }
    }
    int top()
    {
        return _data.top();
    }
    void pop()
    {
        _data.pop();
        _min.pop();
    }
    int getMin()
    {
        return _min.top();
    }

private:
    stack<int> _data;
    stack<int> _min;
};

class MyQueue
{
public:
    void push(int x)
    {
        stack<int> tmep_stack;
        while (!_data.empty())
        {
            tmep_stack.push(_data.top());
            _data.pop();
        }
        while (!tmep_stack.empty())
        {
            _data.push(tmep_stack.top());
            tmep_stack.pop();
        }
    }
    int pop()
    {
        int x = _data.top();
        _data.pop();
        return x;
    }
    int peek()
    {
        return _data.top();
    }
    bool empty()
    {
        return _data.empty();
    }

private:
    stack<int> _data;
};
class MyStack
{
public:
    MyStack()
    {
    }
    void push(int x)
    {
        queue<int> temp_queue;
        temp_queue.push(x);
        while (!_data.empty())
        {
            temp_queue.push(_data.front());
            _data.pop();
        }
        while (!temp_queue.empty())
        {
            _data.push(temp_queue.front());
            temp_queue.pop();
        }
    }
    int pop()
    {
        int x = _data.front();
        _data.pop();
        return x;
    }
    int top()
    {
        return _data.front();
    }
    bool empty()
    {
        return _data.empty();
    }

private:
    queue<int> _data; // 存储的元素顺序就是栈存储元素的顺序
};

// {8,9,9,6,0,2,8,11};
// -1 0 1 0 -1 -2 -3 1
// 9, 9, 6, 0, 6, 6, 9
// 1 1 -1 -1 -1 -1  1
//前缀和>=0,区间和
//     1 2 3 4
//   0 1 3 6 10
// sum[i, j] = s[j] - s[i-1]
/// i-ind[cnt-1] + f[cnt-1] --- 计算最长
// pos(n)-pos(n-1) + f(n-1)
// map ind====-3:6 -2:5 -1:0 0:-1 1:2
// map f======-3:0 -2:0 -1:0 0:0 1:3
int logestWPT(vector<int> &hours)
{
    map<int, int> ind;
    map<int, int> f;
    ind[0] = -1;
    f[0] = 0;
    int cnt = 0, ans = 0; // cnt ----前缀和
    for (int i = 0; i < hours.size(); i++)
    {
        if (hours[i] > 8)
            cnt += 1;
        else
            cnt -= 1;
        if (ind.find(cnt) == ind.end())
        {
            ind[cnt] = i;
            if (ind.find(cnt - 1) == ind.end())
                f[cnt] = 0;
            else
                f[cnt] = f[cnt - 1] + (i - ind[cnt - 1]);
        }
        if (ind.find(cnt - 1) == ind.end())
            continue;
        ans = max(ans, i - ind[cnt - 1] + f[cnt - 1]);
    }
    cout << "map ind===";
    for (auto it = ind.begin(); it != ind.end(); it++)
    {
        printf("%d:%d ", it->first, it->second);
    }
    cout << "map f======";
    for (auto it = f.begin(); it != f.end(); it++)
    {
        printf("%d:%d ", it->first, it->second);
    }
    cout << "" << endl;
    return ans;
}

/// @brief  0:start:1
///         1:start:2
/// @param n
/// @param logs
/// @return
vector<int> exclusiveTime(int n, vector<string> &logs)
{
    vector<int> ans(n);
    stack<int> vID;
    for (int i = 0, pre = 0; i < logs.size(); i++)
    {
        int pos1 = logs[i].find_first_of(":");
        int pos2 = logs[i].find_last_of(":");
        string id_str = logs[i].substr(0, pos1);
        string status = logs[i].substr(pos1 + 1, pos2 - pos1 - 1);
        string time_str = logs[i].substr(pos2 + 1, logs[i].size());
        int id = atoi(id_str.c_str());
        int time_stamp = atoi(time_str.c_str());
        if (!vID.empty())
            ans[vID.top()] += time_stamp - pre + (status == "end");
        pre = time_stamp + (status == "end");
        if (status == "start")
            vID.push(id);
        else
            vID.pop();
    }
    return ans;
}

// int level(char c){
//     switch(c){
//         case '@': return -1;
//         case '+':
//         case '-': return 1;
//         case '*':
//         case '/': return 2;
//     }
//     return 0;
// }
// int calc(int a, char op, int b){
//     switch(op){
//         case '+': return a +b;
//         case '-': return a-b;
//         case '*': return a*b;
//         case '/': return a/b;
//     }
//     return 0;
// }
// int calculate(string s){
//     stack<int> num;
//     stack<char> ops;
//     s += "@";
//     for(int i = 0, num = 0; i < s.size(); i++){
//             if(s[i] == ' ') continue;
//             if(level(s[i]) == 0){
//                 n = n * 10 + (s[i] - '0'); // 将字符变为数字 '123'===>123
//                 continue;
//             }
//             num.push(n);
//             n  = 0;
//             while(!ops.empty() && level(s[i]) <= level(ops.top())){
//                 int b = num.top(); num.pop();
//                 int a = num.top();  num.pop();
//                 num.push(calc(a, ops.top(), b));
//                 ops.pop();
//             }
//             ops.push(s[i]);
//     }
//     return num.top();
// }

// // 9,3,4,#,#,1,#,#,2#,6,#,#   1##---> #
// bool isValidSerialization(string preorder)
// {
//     vector<string> s;
//     for (int i = 0, j = 0; i < preorder.size(); i = j + 1)
//     {
//         j = i;
//         while (j < preorder.size() && preorder[j] != ',')
//             ++j;
//         s.push_back(preorder.substr(i, j - i));
//         int last = s.size() - 1;
//         while (s.size() >= 3 && s[last] == "#" && s[last - 1] == "#" && s[last - 2] != "#")
//         {
//             s[last - 2] = "#";
//             s.pop_back();
//             s.pop_back();
//             last = s.size() - 1;
//         }
//     }
//     return s.size() == 1 && s[0] == "#";
// }

// 要不是當前棧頂元素，要不是未來入棧元素
// bool validateStackSequences(vector<int>& pushed, vector<int>& popped){
//     stack<int> s;
//     for(int i = 0, j = 0; i < popped.size(); i++){
//         while(j < pushed.size() && (s.empty() || s.top() != popped[i])){ //要判斷s棧是否為空，為空或棧頂不等
//             s.push(pushed[j]);
//             j += 1;
//         }
//         if (s.top() != popped[i]) return false;
//         s.pop();
//     }
//     return true;
// }

// 'ab#d'  'ac#d'   #---前一個字符被刪除
// void transform(string S, stack<char> &s)
// {
//     for (int i = 0; i < S.size(); i++)
//     {
//         if (S[i] == "#" && !s.empty())
//             s.pop();
//         else if (S[i] != "#")
//             s.push(S[i]);
//     }
// }
// bool backspaceCompare(string S, string T)
// {
//     stack<char> s;
//     stack<char> t;
//     transform(S, s);
//     transform(T, t);
//     if (s.size() - t.size())
//         return false;
//     while (!s.empty())
//     {
//         if (s.top() != t.top())
//             return false;
//         s.pop(), t.pop();
//     }
//     return true;
// }

// int calPoints(vector<string> &ops)
// {
//     stack<int> s;
//     for (int i = 0; i < ops.size(); i++)
//     {
//         if (ops[i] == "+")
//         { //  a+b---a---b
//             int a = s.top();
//             s.pop();
//             int b = s.top();
//             s.push(a)
//                 s.push(a + b);
//         }
//         else if (ops[i] == "D")
//         {
//             s.push(2 * s.top());
//         }
//         else if (ops[i] == "C")
//         {
//             s.pop();
//         }
//         else
//         {
//             s.push(atoi(ops[i].c_str())); //轉出數字
//         }
//     }
//     int sum = 0;
//     while (!s.empty())
//     {
//         sum += s.top();
//         s.pop();
//     }
//     return sum;
// }

// class MyQueue{
//     public:
//     stack<int> s1, s2;
//     MyQueue(){}
//     void push(int x){
//         s2.push(x);
//         return ;
//     }
//     void transfer(){
//         if(!s1.empty()) return ;
//         while(!s2.empty()){
//             s1.push(s2.top());
//             s2.pop();
//         }
//         return;
//     }
//     int pop(){
//         transfer();
//         int ret = s1.top();
//         s1.pop();
//         return ret;
//     }
//     int peek(){
//         transfer();
//         return s1.top();
//     }
//     bool empty(){
//         return s1.empty() && s2.empty();
//     }
// }

// struct TreeNode
// {
//     int val;
//     TreeNode *left;
//     TreeNode *right;
//     TreeNode() : val(0), left(nullptr), right(nullptr) {}
//     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
//     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
// };

// vector<int> postorderTraversal(TreeNode *root)
// {
//     if (root == nullptr)
//         return vector<int>();
//     vector<int> ans;
//     stack<TreeNode *> s1;   // 遞歸過程中的局部變量
//     stack<int> s2; // 遞歸到的程序位置
//     s1.push(root);
//     s2.push(0);
//     while (!s1.empty())
//     {
//         int status = s2.top();
//         s2.pop();
//         switch (status)
//         {
//         case 0:
//         {
//             s2.push(1);
//             if (s1.top()->left != nullptr)
//             {
//                 s1.push(s1.top()->left);
//                 s2.push(0);
//             }
//             break;
//         }
//         case 1:
//         {
//             s2.push(2);
//             if (s1.top()->right != nullptr)
//             {
//                 s1.push(s1.top()->right);
//                 s2.push(0);
//             }
//         }
//         break;
//         case 2:
//         {
//             ans.push_back(s1.top()->val);
//             s1.pop();
//         }
//         break;
//         }
//     }
// }

// void post_order(Node* root){
//     if(root==NULL) return;
//     post_order(root->left);   // 0 1 2 狀態
//     post_order(root->right);
//     output(root);
//     return;
// }
// 145.   二叉樹的後續遍歷---- 左右根

// // 移除無效括弧 (()) ) l--r 可去掉多餘的右括號 r--l可去掉多餘的左括號
// string minRemoveToMakeValid(string s)
// {
//     char *t = new char[s.size() + 1];
//     char *ans = new char[s.size() + 1];
//     int tlen = 0;
//     for (int i = 0, cnt = 0; i < s.size(); i++)
//     {
//         if (s[i] == '(' || s[i] != ')')
//         {
//             cnt += (s[i] == '(');
//             t[tlen++] = s[i];
//         }
//         else
//         {
//             if (cnt == 0)
//                 continue;
//             cnt -= 1;
//             t[tlen++] = ')';
//         }
//     }
//     ans[tlen] = '\0';
//     int ans_head = tlen;
//     for (int i = tlen - 1, cnt = 0; i >= 0; i--)
//     {
//         if (t[i] == ')' || t[i] != '(')
//         {
//             cnt += (t[i] == ')');
//             ans[--ans_head] = t[i];
//         }
//         else
//         {
//             if (cnt == 0)
//                 continue;
//             cnt -= 1;
//             ans[--ans_head] = '(';
//         }
//     }
//     return string(ans + ans_head);
// }

// // 差值為0---棧空 pre--起始位置   pre---i----i+1
// string removeOuterParentheses(string s)
// {
//     string ret;
//     for (int i = 0, pre = 0, cnt = 0; i < S.size(); i++)
//     {
//         if (S[i] == '(')
//             cnt += 1; // cnt -- 差值/棧頂
//         else
//             cnt -= 1;
//         if (cnt != 0)
//             continue;
//         ret += S.substr(pre + 1, i - pre - 1); // 截取1-目標值0
//         pre = i + 1;                           // 移動到下一位
//     }
//     return ret;
// }

// 输入：s = "()"
// 输出：true
// 输入：s = "()[]{}"
// 输出：true
// 输入：s = "(]"
// 输出：false
// bool isValid(string s)
// {
//     stack<char> ss;
//     map<char, char> valid; // unordered_map<char, char>
//     valid[')'] = '(';
//     valid['}'] = '{';
//     valid[']'] = '[';
//     for (int i = 0; i < s.size(); i++)
//     {
//         switch (s[i])
//         {
//         case '(':
//         case '[':
//         case '{':
//             ss.push(s[i]);
//             break;
//         case ')':
//             // if (ss.empty() || ss.top() != '(')
//             //     return false;
//             // ss.pop();
//             // break;
//         case ']':
//             // if (ss.empty() || ss.top() != '[')
//             //     return false;
//             // ss.pop();
//             // break;
//         case '}':
//             if (ss.empty() || valid[s[i]] != ss.top())
//                 return false;
//             ss.pop();
//             break;
//         }
//     }
// }

// 栈适合处理的问题--完全包含问题
// =================================
// +1-----> 进，-1----->出
// =================================
// 任意位置，左括号数量>右括号数量
// 最后位置，左=右
// class Stack
// {
// public:
//     Statck()
//     {
//         // top = -1;
//     }
//     void push(int x)
//     {
//         // top+=1;
//         // data[top] = x;
//         data.push_back(x);
//         return;
//     }
//     void pop()
//     {
//         if (empty())
//             return;
//         data.pop_back();
//         // top-=1;
//     }
//     bool empty()
//     {
//         // return top == -1;
//         return data.size() == 0;
//     }
//     int size()
//     {
//         // return top + 1;
//         return data.size();
//     }
//     void output()
//     {
//         cout << "=======" << endl;
//         // for(int i = top; i >= 0; i--){
//         //     cout << "  "<< data[i] <<endl;
//         // }
//         for (int i = data.size() - 1; i >= 0; i--)
//         {
//             cout << " " << data[i] << endl;
//         }
//         cout << "======" << endl;
//         return;
//     }
// private:
//     vector<int> data;
//     //  int *data, int top;
// };
// bool isValid(char *s){
//     int32_t lnum = 0, rnum = 0;
//     int32_t len = strlen(s);
//     for(int32_t i = 0; i < len; i++){
//         switch (s[i])
//         {
//         case '(':++lnum; break;
//         case ')': ++rnum; break;
//         default: return false;
//         }
//         if (lnum >= rnum) continue;
//         return false;
//     }
//     return lnum == rnum;
// }

// int calc(char *s, int l, int r)
// {
//     int op = -1, pri = 10000 - 1, cur_pri, temp = 0;
//     for (int i = l; i <= r; i++)
//     {
//         cur_pri = 10000;
//         switch (s[i])
//         {
//         case '+':
//         case '-':
//             cur_pri = 1 + temp;
//             break;
//         case '*':
//         case '/':
//             cur_pri = 2 + temp;
//             break;
//         case '(':
//             temp += 100;
//             break;
//         case ')':
//             temp -= 100;
//             break;
//         }
//         if (cur_pri <= pri)
//         {
//             pri = cur_pri;
//             op = i;
//         }
//     }
//     if (op == -1)
//     {
//         int num = 0;
//         for (int i = l; i <= r; i++)
//         {
//             if (s[i] < '0' || s[i] > '9')
//                 continue;
//             num = num * 10 + (s[i] - '0');
//         }
//         return num;
//     }
//     // printf("calc find : %c\n",s[op]);
//     int a = calc(s, l, op - 1);
//     int b = calc(s, op + 1, r);
//     switch (s[op])
//     {
//     case '+':
//         return a + b;
//     case '-':
//         return a - b;
//     case '*':
//         return a * b;
//     case '/':
//         return a / b;
//     }
//     return 0;
// }
int main()
{
    // char s[100];
    // while (~scanf("%[^\n]s", s))
    // {
    //     getchar();
    //     printf("%s = %d\n", s, calc(s, 0, strlen(s) - 1));
    // }
    // return 0;
    vector<int> wpt = {8, 9, 9, 6, 0, 2, 8, 11};
    auto res = logestWPT(wpt);

    cout << "=====" << res << "\n"
         << endl;

    vector<string> logs = {"0:start:0", "1:start:2", "1:end:5", "0:end:6"};
    auto ans = exclusiveTime(4, logs);
    for (int e : ans)
    {
        cout << e << endl;
    }

    // Stack s;
    // string op;
    // int val;
    // while (cin >> op)
    // {
    //     if (op == "ps")
    //     {
    //         cin >> val;
    //         s.push(val);
    //     }
    //     else if (op == "s")
    //     {
    //         cout << s.size() << endl;
    //     }
    //     else if (op == "pp")
    //     {
    //         s.pop();
    //     }
    //     else if (op == "o")
    //     {
    //         s.output();
    //     }
    // }
}