// https://blog.csdn.net/weixin_44765605/article/details/117909521
public class RBTreev2<K extends Comparable<K>, V> {
    private static final boolean BLACK = true;
    private static final boolean RED = false;
    private RBNode<K, V> root;

    static class RBNode<K extends Comparable<K>, V> {
        private final K key;
        private V value;
        private RBNode<K, V> parent;
        private RBNode<K, V> left;
        private RBNode<K, V> right;
        private boolean color;

        public RBNode(K key, V value, RBNode<K, V> parent) {
            this.key = key;
            this.value = value;
            this.parent = parent;
        }

        public V getValue() {
            return value;
        }

        public boolean isColor() {
            return color;
        }

        public RBNode<K, V> getLeft() {
            return left;
        }

        public RBNode<K, V> getRight() {
            return right;
        }
    }

    public RBNode<K, V> getRoot() {
        return this.root;
    }

    private void leftRotate(RBNode<K, V> node) {
        RBNode<K, V> replaceNode = node.right;
        node.right = replaceNode.left;
        if (replaceNode.left != null) {
            replaceNode.left.parent = node;
        }
        if (node.parent == null) {
            this.root = replaceNode;
        } else if (node.parent.left == node) {
            node.parent.left = replaceNode;
        } else {
            node.parent.right = replaceNode;
        }
        replaceNode.parent = node.parent;
        node.parent = replaceNode;
        replaceNode.left = node;
    }

    private void rightRotate(RBNode<K, V> node) {
        RBNode<K, V> replaceNode = node.left;
        node.left = replaceNode.right;
        if (replaceNode.right != null) {
            replaceNode.right.parent = node;
        }
        if (node.parent == null) {
            this.root = replaceNode;
        } else if (node.parent.right == node) {
            node.parent.right = replaceNode;
        } else {
            node.parent.left = replaceNode;
        }
        replaceNode.parent = node.parent;
        node.parent = replaceNode;
        replaceNode.right = node;
    }

    private boolean colorOf(RBNode<K, V> node) {
        return node == null ? BLACK : node.color;
    }

    public void put(K key, V value) {
        if (this.root == null) {
            this.root = new RBNode<>(key, value, null);
            this.root.color = BLACK;
            return;
        }
        RBNode<K, V> cur = this.root;
        RBNode<K, V> curParent;
        int cmp;
        do {
            curParent = cur;
            cmp = key.compareTo(cur.key);
            if (cmp < 0) {
                cur = cur.left;
            } else if (cmp > 0) {
                cur = cur.right;
            } else {
                cur.value = value;
                return;
            }
        } while (cur != null);
        if (cmp < 0) {
            curParent.left = new RBNode<>(key, value, curParent);
        } else {
            curParent.right = new RBNode<>(key, value, curParent);
        }
        // 插入后调整
        adjustAfterPut(cmp < 0 ? curParent.left : curParent.right);
    }

    private void adjustAfterPut(RBNode<K, V> node) {
        while (node != this.root && colorOf(node.parent) == RED) {
            if (colorOf(node.parent.parent.left) == RED && colorOf(node.parent.parent.right) == RED) {
                // 插入4结点的情况
                node.parent.parent.left.color = BLACK;
                node.parent.parent.right.color = BLACK;
                node.parent.parent.color = RED;
                node = node.parent.parent;
            } else {
                // 插入3结点的情况
                if (node.parent == node.parent.parent.left) {
                    // npp一定为黑, 否则np和npp连续为红, 不可能之前put没调整
                    if (node.parent.right == node) {
                        node = node.parent;
                        leftRotate(node);
                    }
                    node.parent.color = BLACK;
                    node.parent.parent.color = RED;
                    rightRotate(node.parent.parent);
                } else {
                    if (node.parent.left == node) {
                        node = node.parent;
                        rightRotate(node);
                    }
                    node.parent.color = BLACK;
                    node.parent.parent.color = RED;
                    leftRotate(node.parent.parent);
                }
                node = this.root;
            }
        }
        // 如果不断往上插入, 最后一个红结点找不到还能插入的地方, 那么自己就变为一个新的2结点, 增加一层
        this.root.color = BLACK;
    }

    public V get(K key) {
        RBNode<K, V> node = getNode(key);
        return node == null ? null : node.value;
    }

    private RBNode<K, V> getNode(K key) {
        RBNode<K, V> cur = this.root;
        int cmp;
        while (cur != null) {
            cmp = key.compareTo(cur.key);
            if (cmp < 0) {
                cur = cur.left;
            } else if (cmp > 0) {
                cur = cur.right;
            } else {
                break;
            }
        }
        return cur;
    }

    public V remove(K key) {
        RBNode<K, V> deleteNode = getNode(key);
        if (deleteNode == null) {
            return null;
        }
        V deleteValue = deleteNode.value;
        removeNode(deleteNode);
        return deleteValue;
    }

    private void removeNode(RBNode<K, V> deleteNode) {
        if (deleteNode.left != null && deleteNode.right != null) {
            // 找前驱
            RBNode<K, V> replaceNode = predecessorForRemove(deleteNode);
            // 早知道就逻辑替换了, 实际的替换实在是太麻烦了
            exchange(deleteNode, replaceNode);
        }
        if (deleteNode.left != null) {
            if (deleteNode == this.root) {
                // 此时如果被删除的是根(说明树只有两个结点)
                deleteNode.left.parent = null;
                this.root = deleteNode.left;
                this.root.color = BLACK;
            } else {
                // 往下找如果找到的前驱有左结点(目前已经替换), 这个左结点一定是红色结点
                if (deleteNode.parent.left == deleteNode) {
                    deleteNode.parent.left = deleteNode.left;
                } else {
                    deleteNode.parent.right = deleteNode.left;
                }
                deleteNode.left.color = BLACK;
                deleteNode.left.parent = deleteNode.parent;
                // 释放
                deleteNode.left = deleteNode.parent = null;
            }
        } else if (deleteNode.right != null) {
            if (deleteNode == this.root) {
                deleteNode.right.parent = null;
                this.root = deleteNode.right;
                this.root.color = BLACK;
            } else {
                if (deleteNode.parent.left == deleteNode) {
                    deleteNode.parent.left = deleteNode.right;
                } else {
                    deleteNode.parent.right = deleteNode.right;
                }
                deleteNode.right.color = BLACK;
                deleteNode.right.parent = deleteNode.parent;
                deleteNode.right = deleteNode.parent = null;
            }
        } else {
            if (deleteNode == this.root) {
                this.root = null;
                return;
            }
            if (colorOf(deleteNode) == BLACK) {
                // 如果替换后被删除的结点替换到2结点上去, 那么需要调整
                adjustBeforeRemove(deleteNode);
            }
            if (deleteNode.parent.left == deleteNode) {
                deleteNode.parent.left = null;
            } else {
                deleteNode.parent.right = null;
            }
            deleteNode.parent = null;
        }
    }

    private void adjustBeforeRemove(RBNode<K, V> deleteNode) {
        while (deleteNode != this.root && colorOf(deleteNode) == BLACK) {
            // 找兄弟结点
            RBNode<K, V> brotherNode;
            if (deleteNode == deleteNode.parent.left) {
                brotherNode = deleteNode.parent.right;
                if (colorOf(brotherNode) == RED) {
                    // 虽然在红黑树上是兄弟, 但是在2-3-4树上不是, 因此需要旋转后找真正的兄弟
                    brotherNode.color = BLACK;
                    deleteNode.parent.color = RED;
                    leftRotate(deleteNode.parent);
                    brotherNode = deleteNode.parent.right;
                }
                if (colorOf(brotherNode.left) == BLACK && colorOf(brotherNode.right) == BLACK) {
                    // 如果兄弟借不了, 那么就损兄弟
                    brotherNode.color = RED;
                    deleteNode = deleteNode.parent;
                } else {
                    // 如果兄弟能借, 有两个就借两个, 只有一个就借一个顺便给个null
                    // 需要注意的是: 如果兄弟是3结点, 那么需要特定结构才能借, 否则借出的就不是null而是红结点
                    // 这里是手写的时候忘记的
                    if (colorOf(brotherNode.right) == BLACK) {
                        brotherNode.color = RED;
                        brotherNode.left.color = BLACK;
                        rightRotate(brotherNode);
                        brotherNode = deleteNode.parent.right;
                    }
                    brotherNode.color = deleteNode.parent.color;
                    // 借了两个/一个+1一个null的4/3结点, 剩下那个红要染黑
                    brotherNode.right.color = BLACK;
                    deleteNode.parent.color = BLACK;
                    leftRotate(deleteNode.parent);
                    deleteNode = this.root;
                }
            } else {
                brotherNode = deleteNode.parent.left;
                if (colorOf(brotherNode) == RED) {
                    brotherNode.color = BLACK;
                    deleteNode.parent.color = RED;
                    rightRotate(deleteNode.parent);
                    brotherNode = deleteNode.parent.left;
                }
                if (colorOf(brotherNode.left) == BLACK && colorOf(brotherNode.right) == BLACK) {
                    // 如果兄弟借不了, 那么就损兄弟
                    brotherNode.color = RED;
                    deleteNode = deleteNode.parent;
                } else {
                    if (colorOf(brotherNode.left) == BLACK) {
                        brotherNode.color = RED;
                        brotherNode.right.color = BLACK;
                        leftRotate(brotherNode);
                        brotherNode = deleteNode.parent.left;
                    }
                    // 如果兄弟能借, 有两个就借两个, 只有一个就借一个顺便给个null
                    brotherNode.color = deleteNode.parent.color;
                    brotherNode.left.color = BLACK;
                    deleteNode.parent.color = BLACK;
                    rightRotate(deleteNode.parent);
                    deleteNode = this.root;
                }
            }
        }
        // 补偿
        deleteNode.color = BLACK;
    }

    private void exchange(RBNode<K, V> up, RBNode<K, V> down) {
        RBNode<K, V> temp = up.left;
        up.left = down.left;
        if (up.left != null) {
            up.left.parent = up;
        }
        down.left = temp;
        down.left.parent = down;
        temp = up.right;
        up.right = down.right;
        if (up.right != null) {
            up.right.parent = up;
        }
        down.right = temp;
        down.right.parent = down;
        temp = down.parent;
        down.parent = up.parent;
        if (up == this.root) {
            this.root = down;
        } else {
            if (up.parent.left == up) {
                up.parent.left = down;
            } else {
                up.parent.right = down;
            }
        }
        if (temp.left == down) {
            temp.left = up;
        } else {
            temp.right = up;
        }
        up.parent = temp;
        // 换色
        boolean tempColor = up.color;
        up.color = down.color;
        down.color = tempColor;
    }

    private RBNode<K, V> predecessorForRemove(RBNode<K, V> node) {
        RBNode<K, V> cur = node.left;
        while (cur.right != null) {
            cur = cur.right;
        }
        return cur;
    }

}
