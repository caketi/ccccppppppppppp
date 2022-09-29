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