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
        // ???????????????
        adjustAfterPut(cmp < 0 ? curParent.left : curParent.right);
    }

    private void adjustAfterPut(RBNode<K, V> node) {
        while (node != this.root && colorOf(node.parent) == RED) {
            if (colorOf(node.parent.parent.left) == RED && colorOf(node.parent.parent.right) == RED) {
                // ??????4???????????????
                node.parent.parent.left.color = BLACK;
                node.parent.parent.right.color = BLACK;
                node.parent.parent.color = RED;
                node = node.parent.parent;
            } else {
                // ??????3???????????????
                if (node.parent == node.parent.parent.left) {
                    // npp????????????, ??????np???npp????????????, ???????????????put?????????
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
        // ????????????????????????, ???????????????????????????????????????????????????, ?????????????????????????????????2??????, ????????????
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
            // ?????????
            RBNode<K, V> replaceNode = predecessorForRemove(deleteNode);
            // ???????????????????????????, ????????????????????????????????????
            exchange(deleteNode, replaceNode);
        }
        if (deleteNode.left != null) {
            if (deleteNode == this.root) {
                // ??????????????????????????????(???????????????????????????)
                deleteNode.left.parent = null;
                this.root = deleteNode.left;
                this.root.color = BLACK;
            } else {
                // ??????????????????????????????????????????(??????????????????), ????????????????????????????????????
                if (deleteNode.parent.left == deleteNode) {
                    deleteNode.parent.left = deleteNode.left;
                } else {
                    deleteNode.parent.right = deleteNode.left;
                }
                deleteNode.left.color = BLACK;
                deleteNode.left.parent = deleteNode.parent;
                // ??????
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
                // ??????????????????????????????????????????2????????????, ??????????????????
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
            // ???????????????
            RBNode<K, V> brotherNode;
            if (deleteNode == deleteNode.parent.left) {
                brotherNode = deleteNode.parent.right;
                if (colorOf(brotherNode) == RED) {
                    // ??????????????????????????????, ?????????2-3-4????????????, ???????????????????????????????????????
                    brotherNode.color = BLACK;
                    deleteNode.parent.color = RED;
                    leftRotate(deleteNode.parent);
                    brotherNode = deleteNode.parent.right;
                }
                if (colorOf(brotherNode.left) == BLACK && colorOf(brotherNode.right) == BLACK) {
                    // ?????????????????????, ??????????????????
                    brotherNode.color = RED;
                    deleteNode = deleteNode.parent;
                } else {
                    // ??????????????????, ?????????????????????, ????????????????????????????????????null
                    // ??????????????????: ???????????????3??????, ?????????????????????????????????, ????????????????????????null???????????????
                    // ?????????????????????????????????
                    if (colorOf(brotherNode.right) == BLACK) {
                        brotherNode.color = RED;
                        brotherNode.left.color = BLACK;
                        rightRotate(brotherNode);
                        brotherNode = deleteNode.parent.right;
                    }
                    brotherNode.color = deleteNode.parent.color;
                    // ????????????/??????+1??????null???4/3??????, ????????????????????????
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
                    // ?????????????????????, ??????????????????
                    brotherNode.color = RED;
                    deleteNode = deleteNode.parent;
                } else {
                    if (colorOf(brotherNode.left) == BLACK) {
                        brotherNode.color = RED;
                        brotherNode.right.color = BLACK;
                        leftRotate(brotherNode);
                        brotherNode = deleteNode.parent.left;
                    }
                    // ??????????????????, ?????????????????????, ????????????????????????????????????null
                    brotherNode.color = deleteNode.parent.color;
                    brotherNode.left.color = BLACK;
                    deleteNode.parent.color = BLACK;
                    rightRotate(deleteNode.parent);
                    deleteNode = this.root;
                }
            }
        }
        // ??????
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
        // ??????
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
