class TreeNode:
    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None
def maxDepth(self, root: Optional[TreeNode]) -> int:
    def dfs(root, depth):
        if not root:
            return depth
        else:
            return max(dfs(root.left, depth+1), dfs(root.right, depth+1))
    return dfs(root, 0)
# 96. 不同的二叉搜索树 dp[i] i个连续的数字
# dp[6] = sum(  
# 1: dp[0] * dp[5]
# 2: dp[1] * dp[4]
# 3: dp[2] * dp[3]
# 4: dp[3] * dp[2]
# 5: dp[4] * dp[1]
# 6: dp[5] * dp[0]
# )
def numTrees(self, n:int) -> int:
    dp  = [0] *(n+1)
    dp[0] = 1
    for i in range(n+1):
        for j in range(i):
            dp[i] = dp[i] + dp[j] * dp[i-j-1]
    return dp[n]
# l 记录最小值 r记录最大值
def isValidBST(self, root: Optional[TreeNode]) -> bool:
    def valid(root, l, r):
        if not root:
            return True
        if root.val > l and root.val < r:
            l = valid(root.left, l, root.val)
            r = valid(root.right, root.val, r)
            return l and r
        else:
            return False
    return valid(root, float("-inf"), float("inf"))
def isSymmetric(self, root: Optional[TreeNode]) -> bool:
    def dfs(left, right):
        if not left and not right:
            return True
        elif not left and right:
            return False
        elif left and not right:
            return False
        elif left.val != right.val:
            return False
        else:
            return dfs(left.left, right.right) and dfs(left.right,right.left)
    return dfs(root.left, root.right)
def preOrder(root):
    res = []

    def solve(root):
        if not root:
            res.append(root.val)
            solve(root.left)
            solve(root.right)
    solve(root)
    return res


def preOrder01(root):
    if not root:
        return []
    res = []
    stack = []
    stack.append(root)
    while stack:
        root = stack.pop()
        res.append(root.val)
        if root.right:
            stack.append(root.right)
        if root.left:
            stack.append(root.left)
    return res


def inOrder(root):
    res = []

    def solve(root):
        if not root:
            solve(root.left)
            res.append(root.val)
            solve(root.right)
    solve(root)
    return res


def inOrder01(root):
    res = []
    stack = []
    while root or stack:
        if root:
            stack.append(root)
            root = root.left
        else:
            root = stack.pop()
            res.append(root.val)
            root = root.right
    return res


def postOoder(root):
    res = []

    def solve(root):
        if not root:
            solve(root.left)
            solve(root.right)
            res.append(root.val)
    sovle(root)
    return res


def postOrder01(root):
    res = []
    stack = []
    stack.append(root)
    while stack:
        root = stack.pop()
        res.append(root.val)
        if root.left:
            stack.append(root.left)
        if root.right:
            stack.append(root.right)
    return res[::-1]

def levleOrder2(self, root:TreeNode)->List[List[int]]:
    if not root:
        return []
    res = []
    queue = [root]
    while queue:
        tmp = [node.val for node in queue]
        res.append(tmp)
        ll = []
        for node in queue:
            if node.left:
                ll.append(node.left)
            if node.right:
                ll.append(node.right)
            queue = ll
    return res
def levelOrder(root):
    res = []
    queue = []
    queue.append(root)
    while queue:
        root = queue.pop(0)
        res.append(root.val)
        if root.left:
            queue.append(root.left)
        if root.right:
            queue.append(root.right)
    return res


class findModeMost:
    def __init__(self):
        self.pre = TreeNode()
        self.count = 0
        self.max_count = 0
        self.result = []

    def findMode(self, root: TreeNode) -> List[int]:
        if not root:
            return None
        self.search_BST(root)
        return self.result

    def search_BST(self, cur: TreeNode) -> None:
        if not cur:
            return None
        self.search_BST(cur.left)
        # 第一个节点
        if not self.pre:
            self.count = 1
        elif self.pre.val == cur.val:
            self.count += 1
            # 与前一个节点数值不同
        else:
            self.count = 1
        self.pre = cur

        if self.count == self.max_count:
            self.result.append(cur.val)
        if self.count > self.max_count:
            self.max_count = self.count
            self.result = [cur.val]  # 清空self.result

        self.search_BST(cur.right)
# 迭代


class findModeV2:
    def findMode(self, root: TreeNode) -> List[int]:
        stack = []
        cur = root
        pre = None
        maxCount, count = 0, 0
        res = []
        while cur or stack:
            if cur:  # 访问到最底
                stack.append(cur)
                cur = cur.left
            else:  # 处理节点
                cur = stack.pop()
                if pre == None:  # 第一个节点
                    count = 1
                elif pre.val == cur.val:
                    count += 1
                else:
                    count = 1
                if count == maxCount:
                    res.append(cur.val)
                if count > maxCount:
                    maxCount = count
                    res.clear()
                    res.append(cur.val)

                pre = cur
                cur = cur.right
        return result
def buildTree(self, preorder: List[int], inorder: List[int]) -> TreeNode:
    if not preorder or not inorder:
        return None
    root = TreeNode(preorder[0])
    i = inorder.index(preorder[0])
    root.left = self.buildTree(preorder[1:i+1], inorder[:i])
    root.right = self.buildTree(preorder[i+1:], inorder[i+1:])
    return root

def flatten(self, root:TreeNode, pre =None) -> None:
    def dfs(root):
        if not root:
            return
        dfs(root.left)
        dfs(root.right)
        if root.left:
            pre = root.left
            while pre.right:
                pre = pre.right
            pre.right = root.right #右节点挂到左节点的最右边
            root.right = root.left #整个左子树挂到根节点的右边
            root.left = None
        dfs(root)

# 124
def maxPathSum(self, root:TreeNode)->int:
    self.res = float("-inf")
    def dfs(root):
        if not root:
            return 0
        left  = max(dfs(root.left), 0)
        right = max(dfs(root.right), 0)
        self.res = max(self.res, root.val+left+right)

        return root.val+max(left,right)
    dfs(root)
    return self.res