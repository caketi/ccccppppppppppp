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
using namespace std;
// 9,3,4,#,#,1,#,#,2#,6,#,#   1##---> #
bool isValidSerialization(string preorder)
{
    vector<string> s;
    for (int i = 0, j = 0; i < preorder.size(); i = j + 1)
    {
        j = i;
        while (j < preorder.size() && preorder[j] != ',')
            ++j;
        s.push_back(preorder.substr(i, j - i));
        int last = s.size() - 1;
        while (s.size() >= 3 && s[last] == "#" && s[last - 1] == "#" && s[last - 2] != "#")
        {
            s[last - 2] = "#";
            s.pop_back();
            s.pop_back();
            last = s.size() - 1;
        }
    }
    return s.size() == 1 && s[0] == "#";
}

int main(){
    string s = "9,3,4,#,#,1,#,#,2#,6,#,#";
    bool res = isValidSerialization(s);
    cout << "true0 false1::::::\n"<< res << endl; 
    cout << __cplusplus<<endl;
    for(int i : {2 ,3 ,5}){
        cout <<i<<endl;
    }
    string ss;
    ss[0] = '1';
    int n = 1;
    n = n * 10 + (ss[0] - '0');
    cout << n ;
}