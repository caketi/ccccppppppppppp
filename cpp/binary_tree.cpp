#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// struct Node {
// 	Node(int key = 0, Node* left = nullptr, Node* right = nullptr)
// 		: key(key), left(left), right(right) {}
// 	int key;
// 	Node* left;
// 	Node* right;
// };
// // 找前继或后驱
// Node* predeccessor(Node* root) {
// 	Node* temp = root->left;
// 	while (temp->right) temp = temp->right;
// 	return temp;
// }
// void output(Node* root) {
// 	if (root == nullptr) return;
// 	output(root->left);
// 	cout << root->key << ", ";
// 	output(root->right);
// 	return;
// }
// Node* getNewNode(int key) {
// 	return new Node(key);
// }
// void clear(Node* root) {
// 	if (root == nullptr) return;
// 	clear(root->left);
// 	clear(root->right);
// 	delete root;
// 	return;
// }
// Node* insert(Node* root, int key) {
// 	if (root == nullptr) return getNewNode(key);
// 	if (root->key == key) return root;
// 	if (key < root->key) root->left = insert(root->left, key);
// 	else root->right = insert(root->right, key);
// 	return root;
// }
// Node* erase(Node* root, int key) {
// 	if (root == nullptr) return root;
// 	if (key < root->key) {
// 		root->left = erase(root->left, key);
// 	}
// 	else if (key > root->key) {
// 		root->right = erase(root->right, key);
// 	}
// 	else {
// 		if (root->left == nullptr && root->right == nullptr) {
// 			delete root;
// 			return nullptr;
// 		}
// 		else if (root->left == nullptr || root->right == nullptr) {
// 			Node* temp = root->left ? root->left : root->right;
// 			delete root;
// 			return temp;
// 		}
// 		else {
// 			Node* temp = predeccessor(root);
// 			root->key = temp->key;
// 			root->left = erase(root->left, temp->key);
// 		}
// 	}
// 	return root;
// }
#define NIL &(node::__NIL)

struct node {
  node(int key = 0, int h = 0, node *left = NIL, node *right = NIL)
      : key(key), h(h), left(left), right(right) {}
  int key;
  int h;
  node *left, *right;
  static node __NIL;
};
node node::__NIL;

node *getNewNode(int key) { return new node(key, 1); }
void update_height(node *root) {
  root->h = max(root->left->h, root->right->h) + 1;
  return;
}

node *left_rotate(node *root) {
  node *new_root = root->right;
  root->right = new_root->left;
  new_root->left = root;
  update_height(root);
  update_height(new_root);
  return new_root;
}
node *right_rotate(node *root) {
  node *new_root = root->left;
  root->left = new_root->right;
  new_root->right = root;
  update_height(root);
  update_height(new_root);
  return new_root;
}

node *maintain(node *root) {
  if (abs(root->left->h - root->right->h) < 2)
    return root;
  if (root->left->h > root->right->h) {
    if (root->left->right->h > root->left->left->h) {
      root->left = left_rotate(root->left);
    }
    root = right_rotate(root);
  } else {
    if (root->right->left->h > root->right->right->h) {
      root->right = right_rotate(root->right);
    }
    root = left_rotate(root);
  }
  return root;
}

node *insert(node *root, int key) {
  if (root == NIL)
    return getNewNode(key);
  if (root->key == key)
    return root;
  if (key < root->key) {
    root->left = insert(root->left, key);
  } else {
    root->right = insert(root->right, key);
  }
  update_height(root);
  return maintain(root);
}
node *predeccessor(node *root) {
  node *temp = root->left;
  while (temp->right != NIL)
    temp = temp->right;
  return temp;
}
node *erase(node *root, int key) {
  if (root == NIL)
    return root;
  if (key < root->key) {
    root->left = erase(root->left, key);
  } else if (key > root->key) {
    root->right = erase(root->right, key);
  } else {
    if (root->left == NIL || root->right == NIL) {
      node *temp = (root->left == NIL ? root->right : root->left);
      delete root;
      return temp;
    } else {
      node *temp = predeccessor(root);
      root->key = temp->key;
      root->left = erase(root->left, temp->key);
    }
  }
  update_height(root);
  return maintain(root);
}
void clear(node *root) {
  if (root == NIL)
    return;
  clear(root->left);
  clear(root->right);
  delete root;
  cout << "delete : " << root->key << endl;
}

void print(node *root) {
  printf("( %d[%d] | %d, %d)\n", root->key, root->h, root->left->key,
         root->right->key);
  return;
}

void output(node *root) {
  if (root == NIL)
    return;
  print(root);
  output(root->left);
  output(root->right);
  return;
}

int main() {
  int op, val;
  node *root = NIL;
  while (cin >> op >> val) {
    switch (op) {
    case 0:
      root = insert(root, val);
      break;
    case 1:
      root = erase(root, val);
      break;
    case 3:
      break;
    }
    output(root);
  }
  cout << endl << "===== AVL tree print ===" << endl;
  clear(root);
  cout << "=== tree paint done === " << endl;
  return 0;
}

typedef struct Node
{
    int key;
    struct Node* lchild, *rchild;
} Node;

Node* getNewNodeV2(int key){
    Node* p = (Node*)malloc(sizeof(Node));
    p->key = key;
    p->lchild = p->rchild = NULL;
    return p;
}

Node *random_insert(Node* root, int key){
    if (root == NULL) return getNewNodeV2(key);
    if(rand() % 2) {
        root->lchild = random_insert(root->lchild, key);
    } else {
        root->rchild = random_insert(root->rchild, key);
    }
    return root;
}

void pre_order(Node *root){
    if(root==NULL) return ;
    printf("%d ", root->key);
    pre_order(root->lchild);
    pre_order(root->rchild);
    return ;
}
void in_order(Node *root){
    if(root==NULL) return;
    in_order(root->lchild);
    printf("%d ", root->key);
    in_order(root->rchild);
}
// int main(int argc, char *argv[]){
//     srand(time(0));
//     if(argc != 2) return 0;
//     int MAX_N = atoi(argv[1]);
//     Node *root = NULL;
//     for(int i = 1; i <= MAX_N; i++){
//         root = random_insert(root, i);
//     }
//     cout<<"pre_order====="<<endl;
//     pre_order(root);
//      cout<<"\nin_order====="<<endl;
//     in_order(root);
//     return 0;
// }
struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct TreeNode {
  TreeNode *left;
  TreeNode *right;
  int val;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};



// 二叉树最大宽度
typedef pair<TreeNode *, int> PNI;
int widthOfBinaryTree(TreeNode *root) {
  int ans = 0;
  queue<PNI> q;
  q.push(PNI(root, 0));
  while (!q.empty()) {
    int cnt = q.size();
    int l = q.front().second, r = q.front().second;
    for (int i = 0; i < cnt; i++) {
      TreeNode *n = q.front().first;
      int ind = q.front().second;
      r = ind;
      if (n->left)
        q.push(PNI(n->left, (ind - l) * 2)); // ind超界。ind - l。。
      if (n->right)
        q.push(PNI(n->right, (ind - l) * 2 + 1));
      q.pop();
    }
    ans = max(ans, r - l + 1);
  }
  return ans;
}

bool is_Match(TreeNode *A, TreeNode *B) {
  if (B == NULL)
    return true;
  if (A == NULL)
    return false;
  if (A->val != B->val)
    return false;
  return is_Match(A->left, B->left) && is_Match(A->right, B->right);
}

bool isSubStructure(TreeNode *A, TreeNode *B) {
  if (B == NULL)
    return false;
  if (A == NULL)
    return false;
  if (A->val == B->val && is_Match(A, B))
    return true;
  return isSubStructure(A->left, B) || isSubStructure(A->right, B);
}

int getCount(TreeNode *root) {
  if (root == NULL)
    return 0;
  return getCount(root->left) + getCount(root->right) + 1;
}

void in_order(TreeNode *root, vector<int> &ans) {
  if (root == NULL)
    return;
  in_order(root->left, ans);
  ans.push_back(root->val);
  in_order(root->right, ans);
  return;
}

int kthLargest(TreeNode *root, int k) {
  // int cnt_r = getCount(root->right);
  // int cnt_l = getCount(root->left);
  // if(k <= cnt_r) return kthLargest(root->right, k);
  // if( k == cnt_r + 1) return root->val;
  // return kthLargest(root->left, k-cnt_r-1);
  vector<int> ans;
  in_order(root, ans);
  return ans[ans.size() - k];
}

// 前序 中序重建二叉树   pre:root->val|| left || right
// in:   left ||pos ||right
TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
  if (preorder.size() == 0)
    return NULL;
  int pos = 0;
  while (inorder[pos] != preorder[0])
    ++pos; // 找界限
  vector<int> l_pre, l_in, r_pre, r_in;
  for (int i = 0; i < pos; i++) {
    l_pre.push_back(preorder[i + 1]); //[0]---> root
    l_in.push_back(inorder[i]);
  }
  for (int i = pos + 1; i < preorder.size(); i++) {
    r_pre.push_back(preorder[i]);
    r_in.push_back(inorder[i]);
  }
  TreeNode *root = new TreeNode(preorder[0]);
  root->left = buildTree(l_pre, l_in);
  root->right = buildTree(r_pre, r_in);
  return root;
}

int getHeight(TreeNode *root) {
  if (root == NULL)
    return -2;
  int l = getHeight(root->left);
  int r = getHeight(root->right);
  if (l < 0 || r < 0)
    return -2;
  if (abs(l - r) > 1)
    return -2;
  return max(l, r) + 1;
}
bool isBalanced(TreeNode *root) { return getHeight(root) >= 0; }

// 从根到叶
bool hasPathSum(TreeNode *root, int targetSum) {
  if (root == NULL)
    return false;
  if (root->left == NULL && root->right == NULL)
    return root->val == targetSum;
  if (root->left && hasPathSum(root->left, targetSum - root->val))
    return true;
  if (root->right && hasPathSum(root->right, targetSum - root->val))
    return true;
  return false;
}

void reverse(vector<int> &ans) {
  for (int i = 0, j = ans.size() - 1; i < j; i++, j--) {
    swap(ans[i], ans[j]);
  }
  for (int i = 1; i < ans.size(); i += 2) {
    reverse(ans);
  }
  return;
}

// 二叉树层序遍历 自上而下。自下而上.锯齿遍历（s形）（递归、队列）       k :
// 第几个数组 0 1 2 3---层数  父节点：上一层，子节点：下一层
void getResult(TreeNode *root, int k, vector<vector<int>> &ans) {
  if (root == NULL)
    return;
  if (k == ans.size())
    ans.push_back(vector<int>());
  ans[k].push_back(root->val);
  getResult(root->left, k + 1, ans);
  getResult(root->right, k + 1, ans);
  return;
}
vector<vector<int>> levelOrder(TreeNode *root) {
  vector<vector<int>> ans;
  getResult(root, 0, ans);
  // 交换
  for (int i = 0, j = ans.size() - 1; i < j; i++, j--) {
    swap(ans[i], ans[j]);
  }
  return ans;
}
// 翻转二叉树
TreeNode *invertTree(TreeNode *root) {
  if (root == NULL)
    return root;
  swap(root->left, root->right);
  invertTree(root->left);
  invertTree(root->right);
  return root;
}
//      完全二叉树 队，优先队列
// 二叉树   多叉树 字典树，ac自动机，并查集
//         二叉排序树 avl树，红黑树，b树
// dp[0][0] 0-0父子都不放摄像头 本身值代表父子需要放的摄像
void getDP(TreeNode *root, int dp[2][2]) {
  if (root == NULL) { // 当前节点为空
    dp[0][0] = 0;
    dp[0][1] = 111111;
    dp[1][0] = 0;
    dp[1][1] = 111111;
  }
  if (root->left == NULL && root->right == NULL) { // d当前节点为叶子节点
    dp[0][0] = 111111;
    dp[0][1] = 1;
    dp[1][0] = 0;
    dp[1][1] = 1;
  }

  int l[2][2], r[2][2];
  getDP(root->left, l);
  getDP(root->right, r);
  dp[0][0] = min(min(l[0][1] + r[0][0], l[0][0] + r[0][1]), l[0][1] + r[0][1]);
  dp[1][0] = min(dp[0][0], l[0][0] + r[0][0]);
  dp[0][1] = min(min(l[1][0] + r[1][0], l[1][1] + r[1][1]),
                 min(l[1][0] + r[1][1], l[1][1] + r[1][0])) +
             1;
  dp[1][1] = dp[0][1];
  return;
}
int minCameraCover(TreeNode* root){
    int dp[2][2];
    getDP(root, dp);
    return min(dp[0][1],dp[0][0]);
}
// head = [2,4,8] root=[1,4,4,null,2,2,null,1,null,6,8,null,null,null,null,1,3]
bool judge(TreeNode *root, ListNode *head) {
  if (head == nullptr)
    return true;
  if (root == nullptr)
    return false;
  if (root->val != head->val)
    return false;
  return judge(root->left, head->next) || judge(root->right, head->next);
}

bool isSubPath(ListNode *head, TreeNode *root) {
  if (head == nullptr)
    return true;
  if (root == nullptr)
    return false;
  if (root->val == head->val && judge(root, head))
    return true;
  return isSubPath(head, root->left) || isSubPath(head, root->right);
}

int nodeCount(TreeNode *root) {
  if (root == nullptr)
    return 0;
  return nodeCount(root->left) + nodeCount(root->right) + 1;
}
bool judge(TreeNode *root, int n, int m) {
  if (root == nullptr)
    return n == 0;
  if (n == 0)
    return false;
  if (n == 1)
    return root->left == nullptr && root->right == nullptr;
  int k = max(0, 2 * m - 1);
  int l = min(m, n - k), r = n - k - l;
  return judge(root->left, (k - 1) / 2 + l, m / 2) &&
         judge(root->right, (k - 1) / 2 + r, m / 2);
}
bool isCompleteTree(TreeNode *root) {
  if (root == nullptr)
    return true;
  int n = nodeCount(root), m = 1, cnt = 1;
  while (cnt + 2 * m <= n) {
    m *= 2;
    cnt += m;
  }
  return judge(root, n, m);
}

class treetoDobuleList {
  struct Node {
    int val;
    Node *left;
    Node *right;
    Node() : val(0), left(nullptr), right(nullptr) {}
    Node(int val, Node *left, Node *right)
        : val(val), left(left), right(right) {}
  };
  Node *head, *pre;
  void in_order(Node *root) {
    if (root == nullptr)
      return;
    in_order(root->left);
    if (pre == nullptr) {
      head = root;
    } else {
      pre->right = root;
    }
    root->left = pre;
    pre = root;
    in_order(root->right);
    return;
  }
  Node *treeToDoubleyList(Node *root) {
    if (root == nullptr)
      return nullptr;
    head = pre = nullptr;
    in_order(root);
    head->left = pre;
    pre->right = head;
    return head;
  }
};

class CaniWin {
  unordered_map<int, bool> h;
  bool dfs(int mask, int n, int total) {
    if (h.find(mask) != h.end())
      return h[mask];
    for (int i = 1; i <= n; i++) {
      if (mask & (1 << i))
        continue;
      if (i >= total || !dfs(mask | (1 << i), n, total - i)) // 我赢/对手输
      {
        return h[mask] = true;
      }
    }
    return h[mask] = false;
  }
  bool canIWin(int maxChoosableInteger, int desiredTotal) {
    int n = maxChoosableInteger, mask = 0;
    if ((1 + n) * n / 2 < desiredTotal) // 相加和小于目标的情况，非法
      return false;
    h.clear();
    return dfs(mask, maxChoosableInteger, desiredTotal);
  }
};

// 随机打乱数组
vector<int> nums;
vector<int> shuffle() {
  vector<int> ret(nums);
  for (int i = 0; i < ret.size(); i++) {
    swap(ret[i], ret[rand() % ret.size()]);
  }
  return ret;
}

class PathSum {
  unordered_map<int, int> h;
  int count(TreeNode *root, int sum, int targetSum) {
    if (root == nullptr)
      return 0;
    sum += root->val;
    int ans = h[sum - targetSum];
    h[sum] += 1;
    ans += count(root->left, sum, targetSum);
    ans += count(root->right, sum, targetSum);
    h[sum] -= 1;
    return ans;
  }
  int pathSum(TreeNode *root, int targetSum) {
    h.clear();
    h[0] = 1;
    return count(root, 0, targetSum);
  }
  vector<vector<int>> pathSum_v2(TreeNode *root, int sum) {
    vector<vector<int>> result;
    vector<int> path;   // 路径栈
    int path_value = 0; // 路径值
    preorder(root, path_value, sum, path, result);
    return result;
  }
  void preorder(TreeNode *node, int &path_value, int sum, vector<int> &path,
                vector<vector<int>> &result) {
    if (!node) {
      return;
    }
    path_value += node->val;
    path.push_back(node->val);
    if (!node->left && !node->right && path_value == sum) {
      result.push_back(path);
    }
    preorder(node->left, path_value, sum, path, result);
    preorder(node->right, path_value, sum, path, result);
    path_value -= node->val;
    path.pop_back();
  }
};

class flattenTree_v2 {
  void flattern(TreeNode *root) {
    TreeNode *last = NULL;
    preorder(root, last);
  }
  void preorder(TreeNode *node, TreeNode *&last) {
    if (!node) {
      return;
    }
    if (!node->left && !node->right) {
      last = node;
      return;
    }
    TreeNode *left = node->left;
    TreeNode *right = node->right;
    TreeNode *left_last = nullptr;
    TreeNode *right_last = nullptr;
    if (left) {
      preorder(left, left_last);
      node->left = nullptr;
      node->right = left;
      last = left_last;
    }
    if (right) {
      preorder(right, right_last);
      if (left_last) {
        left_last->right = right;
      }
      last = right_last;
    }
  }
};
class flattenTree {
  void flattern(TreeNode *root) {
    vector<TreeNode *> node_vec;
    preorder(root, node_vec);
    for (int i = 1; i < node_vec.size(); i++) {
      node_vec[i - 1]->left = nullptr;
      node_vec[i - 1]->right = node_vec[i];
    }
  }
  void preorder(TreeNode *node, vector<TreeNode *> &node_vec) {
    if (!node) {
      return;
    }
    node_vec.push_back(node);
    preorder(node->left, node_vec);
    preorder(node->right, node_vec);
  }
};

class lowestCommAncestor {

  TreeNode *lCA(TreeNode *root, TreeNode *p, TreeNode *q) {
    if (root == q || root == p || root == NULL)
      return root;
    TreeNode *left = lCA(root->left, p, q);
    TreeNode *right = lCA(root->right, p, q);
    if (left != NULL && right != NULL)
      return root;
    if (left == NULL)
      return right;
    return left;
  }
  void preorder(TreeNode *node, TreeNode *search, vector<TreeNode *> &path,
                vector<TreeNode *> &result, int &finish) {
    if (!node || finish) {
      return;
    }
    path.push_back(node); // path尾部压入，
    if (node == search) {
      finish = 1;
      result = path;
    }
    preorder(node->left, search, path, result, finish);
    preorder(node->right, search, path, result, finish);
    path.pop_back();
  }
  TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
    vector<TreeNode *> path;
    vector<TreeNode *> node_p_path;
    vector<TreeNode *> node_q_path;
    int finish = 0;

    preorder(root, p, path, node_p_path, finish);
    path.clear(); // 清空path。finish
    finish = 0;
    preorder(root, q, path, node_q_path, finish);
    int path_len = 0;
    if (node_p_path.size() < node_q_path.size()) {
      path_len = node_p_path.size();
    } else {
      path_len = node_q_path.size();
    }
    TreeNode *result = 0;
    for (int i = 0; i < path_len; i++) {
      if (node_q_path[i] ==
          node_p_path
              [i]) // 最近公共祖先，两条路径一定有公共的节点，path中存的节点从根节点开始
      {
        result = node_p_path[i];
      }
    }
    return result;
  }
};

vector<int> rightSideView(TreeNode *root) {
  vector<int> view;               // 按层遍历的最后一个节点
  queue<pair<TreeNode *, int>> Q; // 宽度优先搜索队列<节点，层数>
  if (root) {
    Q.push(make_pair(root, 0));
  } // 根节点非空，将<root, 0>push进queue
  while (!Q.empty()) {
    TreeNode *node = Q.front().first; // 搜索节点
    int depth = Q.front().second;     // 待搜索节点的层数
    Q.pop();
    if (view.size() == depth) { // 新遇到
      view.push_back(node->val);
    } else {
      view[depth] = node->val;
    }
    if (node->left) {
      Q.push(make_pair(node->left, depth + 1));
    }
    if (node->right) {
      Q.push(make_pair(node->right, depth + 1));
    }
  }
  return view;
}
class recoverTre {
  TreeNode *pre, *q, *p;
  void inorder(TreeNode *root) {
    if (root == nullptr)
      return;
    inorder(root->left);
    if (pre && root->val < pre->val) {
      if (p == nullptr)
        p = pre;
      q = root;
    }
    pre = root;
    inorder(root->right);
    return;
  }
  void recoverTree(TreeNode *root) {
    pre = q = p = nullptr;
    inorder(root);
    swap(p->val, q->val);
    return;
  }
};

class findSumTar {
  void inorder(TreeNode *root, vector<int> &ret) {
    if (root == nullptr)
      return;
    inorder(root->left, ret);

    ret.push_back(root->val);
    inorder(root->right, ret);
    return;
  }
  bool findTarget(TreeNode *root, int k) {
    vector<int> ret;
    inorder(root, ret);
    int p = 0, q = ret.size() - 1;
    while (p < q && ret[p] + ret[q] - k) {
      if (ret[p] + ret[q] < k)
        p += 1;
      else
        q -= 1;
    }
    return p < q;
  }
};

// n = 10 --- 4 小于10的质数一共4个，2,3,5,7
int countPrimes(int n) {
  int *prime = new int[n + 1];
  for (int i = 0; i < n; i++)
    prime[i] = 0;
  for (int i = 2; i * i < n; i++) {
    if (prime[i])
      continue;
    for (int j = 2 * i; j < n; j += 1) {
      prime[j] = 1;
    }
  }
  int cnt = 0;
  for (int i = 2; i < n; i++)
    cnt += (prime[i] == 0);
  delete[] prime;
  return cnt;
}

struct BSTNode {
  int val;
  int count;
  BSTNode *left;
  BSTNode *right;
  BSTNode(int x) : val(x), left(NULL), right(NULL), count(0) {}
};
void BST_insert(BSTNode *node, BSTNode *insert_node, int &count_small) {
  if (insert_node->val <= node->val) {
    node->count++; // 左子树节点数量
    if (node->left) {
      BST_insert(node->left, insert_node, count_small);
    } else {
      node->left = insert_node;
    }
  } else {
    count_small += node->count + 1; // 根节点+左子树
    if (node->right) {
      BST_insert(node->right, insert_node, count_small);
    } else {
      node->right = insert_node;
    }
  }
}
vector<int> countSmaller(vector<int> &nums) {
  vector<int> result;
  vector<BSTNode *> node_vec;
  vector<int> count;
  for (int i = nums.size() - 1; i >= 0; i--) {
    node_vec.push_back(new BSTNode(nums[i]));
  }
  count.push_back(0);
  for (int i = 1; i < node_vec.size(); i++) {
    int count_small = 0;
    BST_insert(node_vec[0], node_vec[i], count_small);
    count.push_back(count_small);
  }
  for (int i = node_vec.size() - 1; i >= 0; i--) {
    delete node_vec[i];
    result.push_back(count[i]);
  }
  return result;
}
