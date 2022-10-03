class TreeNode:
    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None


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
