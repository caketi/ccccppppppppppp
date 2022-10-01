public class RBTree<K extends Comparable<K>, V> {

    /**
     * 将黑定义为true
     */
    private static final boolean BLACK = true;

    /**
     * 将红定义为false
     */
    private static final boolean RED = false;

    /**
     * 根结点
     */
    private RBNode<K, V> root;

    /**
     * 静态内部类, 用于作为RBTree的结点的数据结构(这里就不用getter/setter方法了, 因为外部类能直接
     * 用数据结构里的私有属性, 但是我不希望别的地方的类直接修改结点的值)
     * @param <K> key, 需要实现Comparable接口, 因为需要比较
     * @param <V> value
     */
    static class RBNode<K extends Comparable<K>, V> {

        /**
         * 父结点
         */
        private RBNode<K, V> parent;

        /**
         * 左结点
         */
        private RBNode<K, V> left;

        /**
         * 右结点
         */
        private RBNode<K, V> right;

        /**
         * 结点颜色, 初始化后是红, 因为false代表红色
         */
        private boolean color;

        /**
         * key
         */
        private K key;

        /**
         * value
         */
        private V value;

        /**
         * 构造方法
         * @param key    key
         * @param value  value
         * @param parent 父亲结点
         */
        private RBNode(K key, V value, RBNode<K, V> parent) {
            this.key = key;
            this.value = value;
            this.parent = parent;
        }

        public RBNode<K, V> getLeft() {
            return left;
        }

        public RBNode<K, V> getRight() {
            return right;
        }

        public V getValue() {
            return value;
        }

        public boolean isColor() {
            return color;
        }
    }

    /**
     * 左旋操作, 围绕结点node左旋
     * @param node 要左旋的结点
     */
    private void leftRotate(RBNode<K, V> node) {
        if (node != null) {
            // 1.新的代替node位置的结点
            RBNode<K, V> nr = node.right;
            node.right = nr.left;
            if (nr.left != null) {
                // 修改nr.left的父结点
                nr.left.parent = node;
            }
            // 2.修改新结点nr的父亲为旧结点node的父亲
            // 让新的代替node结点位置的结点的父亲改为node的父亲
            nr.parent = node.parent;
            // 让node的父结点的指针指向新的儿子
            if (node.parent == null) {
                // 如果node为根结点, 那么左旋后node的左儿子nr变为新的根结点
                this.root = nr;
            } else if (node.parent.left == node) {
                // 如果node为node父结点的左儿子
                node.parent.left = nr;
            } else {
                // 如果node为node父结点的右儿子
                node.parent.right = nr;
            }
            // 3.旧结点node下沉为新结点nr的儿子结点
            // node要下沉为儿子了
            nr.left = node;
            // 此时node的父结点处理完了, 因此node的新的父结点要更新了
            node.parent = nr;
        }
    }

    /**
     * 右旋操作, 围绕结点node右旋
     * @param node 要右旋的结点
     */
    private void rightRotate(RBNode<K, V> node) {
        if (node != null) {
            // 1.新的代替node位置的结点
            RBNode<K, V> nl = node.left;
            node.left = nl.right;
            if (nl.right != null) {
                // 挂到node左边的结点要修改自己的父亲
                nl.right.parent = node;
            }
            // 2.修改新结点nl的父亲为旧结点node的父亲
            nl.parent = node.parent;
            if (node.parent == null) {
                // 如果旧结点的父亲为null, 说明原来的旧结点时根结点
                this.root = nl;
            } else if (node.parent.left == node) {
                // 修改父结点的左结点为新结点
                node.parent.left = nl;
            } else {
                // 修改父结点的右结点为新结点
                node.parent.right = nl;
            }
            // 3.旧结点node下沉为新结点nl的儿子结点
            nl.right = node;
            node.parent = nl;
        }
    }

    /**
     * 新增操作
     * @param key   key
     * @param value value
     */
    public void put(K key, V value) {
        if (key == null) {
            // 异常判断
            throw new NullPointerException();
        }
        // 1.构建新结点并判断是否是根结点
        RBNode<K, V> curNode = this.root;
        if (curNode == null) {
            // 如果插入的位置是根结点, 直接赋值即可(根结点需要染黑)
            this.root = new RBNode<>(key, value, null);
            this.root.color = BLACK;
            return;
        }

        // 2.如果插入的位置不是根结点, 则寻找插入位置
        RBNode<K, V> parent;
        int compareResult;
        do {
            // 沿着根结点寻找插入位置
            parent = curNode;
            compareResult = key.compareTo(curNode.key);
            if (compareResult < 0) {
                // 如果大于0, 则要插入的结点key大, 小于0则要插入的结点key更小
                curNode = curNode.left;
            } else if (compareResult > 0) {
                curNode = curNode.right;
            } else {
                // 如果要插入的结点的key早已存在, 则只替换value
                curNode.value = value;
                return;
            }
        } while (curNode != null);
        // 找到要插入的位置, 构建一个红结点并插入
        RBNode<K, V> node = new RBNode<>(key, value, parent);
        // 插入到parent的哪个位置
        if (compareResult < 0) {
            parent.left = node;
        } else {
            parent.right = node;
        }

        // 3.结点挂到树上后, 判断是否要调整(调整: 旋转+变色)
        fixAfterPut(node);
    }

    /**
     * 调整刚插入的结点(红色的), 旋转+变色
     * 1. 2-3-4树:
     *            新增元素+2结点 合并: 直接合并成为一个3结点即可
     *     红黑树:
     *            新增的一个红色结点+黑色父亲结点=上黑下红, 不需要调整
     * 2. 2-3-4树:
     *            新增元素+3结点 合并: 合并成一个4结点
     *     红黑树:
     *            情况1:插+红黑(下中上) 情况2:黑红+插(上中下) 插+黑红(中上中) 红黑+插(中上中) 前两个需要调整, 后面两个不需要调整
     *            红黑树对应的3结点的最终形态是 中上中(红黑红) 因此通过旋转和染色转为 中上中(红黑红)的情况
     * 3. 2-3-4树:
     *            新增元素+4结点 裂开: 2结点+2结点(父, 从原先的4结点中间元素裂出)+3结点
     *     红黑树:
     *            情况3:叔祖父(红黑红)+插 插入结点的祖父变黑, 祖父的两个儿子变红(裂开), 如果祖结点为根, 继续变黑
     * @param node 刚插入的结点
     */
    private void fixAfterPut(RBNode<K, V> node) {
        // 插入结点插入在黑结点下不需要调整, 否则就要调整, 以下是要调整的
        while (node.parent != null && node.parent.color == RED) {
            // 插入左边+3结点(插+红黑(下中上))的情况
            if (node.parent == node.parent.parent.left) {
                // 不需要判断node的祖父是否为空, 因为node的父亲为红, 则node的父亲一定有父亲
                if (colorOf(node.parent.parent.right) == RED) {
                    // 情况3 分裂出来的红结点相当于往上挤, 如果上面是黑, 则直接加入, 否则需要继续分裂
                    // 如果叔叔结点是红色, 则说明插入的是一个4结点, 因此需要裂开
                    // 父 叔设置为黑, 祖父设置为红
                    node.parent.color = BLACK;
                    node.parent.parent.right.color = BLACK;
                    node.parent.parent.color = RED;
                    // 因为祖父结点变为红, 所以可能出现祖父结点的父结点为红的情况, 需要继续调整
                    // 调整会在while中的时候遇到node的父亲为黑或者node的父亲为根的时候结束
                    node = node.parent.parent;
                } else {
                    // 情况1
                    if (node.parent.right == node) {
                        // 如果node插入的是父结点的右边, 则需要左旋后变为情况1
                        // 旋转后node的parent在下面了
                        node = node.parent;
                        leftRotate(node);
                    }
                    // 如果叔叔为黑色, 则说明插入的是一个3结点, 因此需要旋转
                    node.parent.color = BLACK;
                    node.parent.parent.color = RED;
                    // 右旋
                    rightRotate(node.parent.parent);
                }
            } else {
                // 3结点+插入右边(黑红插(上中下))的情况
                if (colorOf(node.parent.parent.left) == RED) {
                    // 情况3
                    // 如果叔叔结点是红色, 则说明插入的是一个4结点, 因此需要裂开
                    // 父 叔设置为黑, 祖父设置为红
                    node.parent.color = BLACK;
                    node.parent.parent.left.color = BLACK;
                    node.parent.parent.color = RED;
                    // 因为祖父结点变为红, 所以可能出现祖父结点的父结点为红的情况, 需要继续调整
                    node = node.parent.parent;
                } else {
                    // 情况2
                    if (node.parent.left == node) {
                        // 如果node插入的是父结点的右边, 则需要右后变为情况2
                        // 旋转后node的parent在下面了
                        node = node.parent;
                        rightRotate(node);
                    }
                    // 如果叔叔为黑色, 则说明插入的是一个3结点, 因此需要旋转
                    node.parent.color = BLACK;
                    node.parent.parent.color = RED;
                    // 左旋
                    leftRotate(node.parent.parent);
                }
            }
        }
        this.root.color = BLACK;
    }

    /**
     * 获取结点颜色
     * @param node 结点
     * @return     返回结点颜色
     */
    private boolean colorOf(RBNode<K, V> node) {
        // 空结点是黑色
        return node == null ? BLACK : node.color;
    }

    /**
     * 根据key删除结点
     * @param key key
     * @return    返回删除的结点对应的value
     */
    public V remove(K key) {
        RBNode<K, V> node = getNode(key);
        if (node == null) {
            return null;
        }
        V removeValue = node.value;
        deleteNode(node);
        return removeValue;
    }

    /**
     * 删除node
     * 情况1. 删除叶子结点, 直接删除
     * 情况2. 删除结点只有一个子结点, 那么用子结点来代替(对于红黑树, 化成2-3-4树后, 结点只有一个子结点的情况只出现
     *                                           在对应的2-3-4树的叶子中, 即使是2-3-4树中非叶子的2结点, 它
     *                                           也有两个儿子, 否则就不满足2-3-4树了, 那么对应到红黑树中, 这
     *                                           个在2-3-4树中的非叶子结点, 在红黑树中是一个黑色结点, 它有两
     *                                           个孩子. 红黑树中红色非叶子结点也是有两个孩子的. 因此对于情况1
     *                                           和情况2对应的要删除结点, 都是对应到2-3-4树的叶子上
     *                                           总结: 删除的红黑树的情况1和情况2的结点, 都对应到2-3-4树的叶子上)
     * 情况3. 如果删除的结点有两个子结点, 此时需要找到前驱结点或后继结点来替代
     * @param deleteNode 要删除的node
     */
    private void deleteNode(RBNode<K, V> deleteNode) {
        // 情况3: node结点有两个孩子, 转为情况2或1后按情况2或1处理
        if (deleteNode.left != null && deleteNode.right != null) {
            // 用后继结点来替代
            RBNode<K, V> replaceNode = successor(deleteNode);
            // 逻辑替代, 这样子不需要修改很多个指针(6个左右)
            deleteNode.key = replaceNode.key;
            deleteNode.value = replaceNode.value;
            // 此时新的deleteNode结点一定没有两个儿子, 否则这个replaceNode不是当前的replaceNode
            deleteNode = replaceNode;
        }
        // 此时要删除的结点可能是新的删除结点
        RBNode<K, V> replaceNode = deleteNode.left != null ? deleteNode.left : deleteNode.right;
        if (replaceNode != null) {
            // 情况2
            // 要删除的结点如果有子树(也只能有一棵子树, 因为如果有两棵的话, 在情况3的处理那里就变成一棵了)
            // 替代者的父指针指向被删除结点的父亲
            replaceNode.parent = deleteNode.parent;
            if (deleteNode.parent == null) {
                // 如果要删除的结点为根结点
                this.root = replaceNode;
            } else if (deleteNode == deleteNode.parent.left){
                // 否则, 如果deleteNode有父亲, 则判断往哪边挂替代的子树
                deleteNode.parent.left = replaceNode;
            } else {
                deleteNode.parent.right = replaceNode;
            }
            // 释放掉deleteNode的所有指针(虽然感觉这一步没什么必要)
            deleteNode.left = deleteNode.right = deleteNode.parent = null;
            // 替换结束后需要调整平衡(红结点不需要调整, 因为红黑树的平衡是黑色结点的平衡)
            if (deleteNode.color == BLACK) {
                // 对于情况2, 如果删的是对应2-3-4树中的叶子结点中的一个, 且它对应到红黑树上是黑的
                // 那么此时这个替代结点一定是红的
                // 让这个替代结点作为对应的2-3-4树的叶子结点, 对应的红黑树的黑结点
                replaceNode.color = BLACK;
            }
        } else {
            // 情况1: 如果删除结点是叶子结点
            if (deleteNode.parent == null) {
                // 如果要删除的结点是根结点
                this.root = null;
            } else {
                if (deleteNode.color == BLACK) {
                    // 如果是deleteNode黑叶子结点, 删除前需要调整
                    fixBeforeRemove(deleteNode);
                }
                // 再删除
                if (deleteNode.parent.left == deleteNode) {
                    deleteNode.parent.left = null;
                } else if (deleteNode.parent.right == deleteNode) {
                    deleteNode.parent.right = null;
                }
                deleteNode.parent = null;
            }
        }
    }

    /**
     * 当删除的结点对应到2-3-4树上是一个2结点的时候, 需要调整
     * 注意: 该方法处理的是非根的2结点
     * 分三种情况:
     * 情况1: 删的是3结点, 只需要染色, 该操作不在这里完成
     * 情况2: 找兄弟借, 兄弟能借
     * 情况3: 找兄弟借, 兄弟不能借
     * @param deleteNode 被删除的结点
     */
    private void fixBeforeRemove(RBNode<K, V> deleteNode) {
        // 找兄弟结点
        while (deleteNode != this.root && colorOf(deleteNode) == BLACK) {
            if (deleteNode == deleteNode.parent.left) {
                // deleteNode是左孩子的情况
                // 找对应的2-3-4树上的兄弟结点
                RBNode<K, V> deleteNodeBrother = deleteNode.parent.right;
                // 判断此时兄弟结点是否是对应的2-3-4树上的兄弟结点
                if (colorOf(deleteNodeBrother) == RED) {
                    // 如果是红色, 那么对应到2-3-4树上, 这个红结点其实是父结点
                    deleteNodeBrother.parent.color = RED;
                    deleteNodeBrother.color = BLACK;
                    leftRotate(deleteNode.parent);
                    deleteNodeBrother = deleteNode.parent.right;
                }
                // 找到真正的兄弟结点后
                if (colorOf(deleteNodeBrother.left) == BLACK && colorOf(deleteNodeBrother.right) == BLACK) {
                    // 情况3: 找兄弟借, 兄弟不能借(这里null为BLACK)
                    // 用红黑树的性质去删, 此时当前路径上少了一个黑结点, 根据红黑树性质, 那么我们可以尝试将
                    // 兄弟结点变红, 这样对于parent来说它的两个子树都是黑色平衡了, 但是如果parent是黑色的话, 那么对于
                    // parent的parent来说是有一边少了个黑的, 于是再损parent的parent另外一边的黑为红, 直到parent为红
                    // 后就停止, 最后把这个红的parent染黑, 那么就能继续维持左右黑色平衡了
                    // 这个brother会是黑的, 因为上面找到了
                    // 先损掉兄弟, 然后再补回来
                    deleteNodeBrother.color = RED;
                    deleteNode = deleteNode.parent;
                } else {
                    // 情况2: 找兄弟借, 兄弟能借
                    // 情况a: 兄弟结点是3结点 情况b: 兄弟结点是4结点
                    if (colorOf(deleteNodeBrother.right) == BLACK) {
                        // 兄弟右孩子为空, 那么左孩子不为空(这里只有3结点的一种情况才会旋, 4结点和3结点的另外一种情况不用旋)
                        deleteNodeBrother.left.color = BLACK;
                        deleteNodeBrother.color = RED;
                        rightRotate(deleteNodeBrother);
                        deleteNodeBrother = deleteNode.parent.right;
                    }
                    // 这个兄弟要去顶替父亲, 所以先变成父亲的颜色
                    deleteNodeBrother.color = deleteNodeBrother.parent.color;
                    deleteNodeBrother.parent.color = BLACK;
                    deleteNodeBrother.right.color = BLACK;
                    leftRotate(deleteNodeBrother.parent);
                    // 调整结束, 跳出循环
                    deleteNode = this.root;
                }
            } else {
                // deleteNode是右孩子的情况
                // 找对应的2-3-4树上的兄弟结点
                RBNode<K, V> deleteNodeBrother = deleteNode.parent.left;
                // 判断此时兄弟结点是否是对应的2-3-4树上的兄弟结点
                if (colorOf(deleteNodeBrother) == RED) {
                    // 如果是红色, 那么对应到2-3-4树上, 这个红结点其实是父结点
                    deleteNodeBrother.parent.color = RED;
                    deleteNodeBrother.color = BLACK;
                    rightRotate(deleteNode.parent);
                    deleteNodeBrother = deleteNode.parent.left;
                }
                // 找到真正的兄弟结点后
                if (colorOf(deleteNodeBrother.left) == BLACK && colorOf(deleteNodeBrother.right) == BLACK) {
                    // 情况3: 找兄弟借, 兄弟不能借(这里null为BLACK)
                    // 用红黑树的性质去删, 此时当前路径上少了一个黑结点, 根据红黑树性质, 那么我们可以尝试将
                    // 兄弟结点变红, 这样对于parent来说它的两个子树都是黑色平衡了, 但是如果parent是黑色的话, 那么对于
                    // parent的parent来说是有一边少了个黑的, 于是再损parent的parent另外一边的黑为红, 直到parent为红
                    // 后就停止, 最后把这个红的parent染黑, 那么就能继续维持左右黑色平衡了
                    // 这个brother会是黑的, 因为上面找到了
                    // 先损掉兄弟, 然后再补回来
                    deleteNodeBrother.color = RED;
                    deleteNode = deleteNode.parent;
                } else {
                    // 情况2: 找兄弟借, 兄弟能借
                    // 情况a: 兄弟结点是3结点 情况b: 兄弟结点是4结点
                    if (colorOf(deleteNodeBrother.left) == BLACK) {
                        // 兄弟右孩子为空, 那么左孩子不为空(这里只有3结点的一种情况才会旋, 4结点和3结点的另外一种情况不用旋)
                        deleteNodeBrother.right.color = BLACK;
                        deleteNodeBrother.color = RED;
                        leftRotate(deleteNodeBrother);
                        deleteNodeBrother = deleteNode.parent.left;
                    }
                    // 这个兄弟要去顶替父亲, 所以先变成父亲的颜色
                    deleteNodeBrother.color = deleteNodeBrother.parent.color;
                    deleteNodeBrother.parent.color = BLACK;
                    deleteNodeBrother.left.color = BLACK;
                    rightRotate(deleteNodeBrother.parent);
                    // 调整结束, 跳出循环
                    deleteNode = this.root;
                }
            }
        }
        deleteNode.color = BLACK;
    }

    /**
     * 获取node的前驱结点
     * @param node node
     * @return     node的前驱结点
     */
    private RBNode<K, V> predecessor(RBNode<K, V> node) {
        if (node == null) {
            return null;
        } else if (node.left != null) {
            RBNode<K, V> cur = node.left;
            while (cur.right != null) {
                cur = cur.right;
            }
            return cur;
        }
        // 左子树为空, 此时如果还要找前驱, 则需要往上找, 找到第一个转弯的地方就是node的前驱
        // 但是这里的代码在删除中用不到, 删除的时候不会运行这段代码
        RBNode<K, V> cur = node.parent;
        RBNode<K, V> parent = node.parent;
        while (parent != null && cur == parent.left) {
            cur = parent;
            parent = parent.parent;
        }
        // parent如果为null则说明没有前驱
        return parent;
    }

    /**
     * 获取node的后继结点
     * @param node node
     * @return     node的后继结点
     */
    private RBNode<K, V> successor(RBNode<K, V> node) {
        if (node == null) {
            return null;
        } else if (node.right != null) {
            RBNode<K, V> cur = node.right;
            while (cur.left != null) {
                cur = cur.left;
            }
            return cur;
        }
        // 右子树为空, 此时如果还要找后继, 则需要往上找, 找到第一个转弯的地方就是node的后继
        // 但是这里的代码在删除中用不到, 删除的时候不会运行这段代码
        RBNode<K, V> cur = node.parent;
        RBNode<K, V> parent = node.parent;
        while (parent != null && cur == parent.right) {
            cur = parent;
            parent = parent.parent;
        }
        // parent如果为null则说明没有后继
        return parent;
    }

    /**
     * 根据key获取结点
     * @param key key
     * @return    key对应的结点
     */
    private RBNode<K, V> getNode(K key) {
        if (key == null) {
            return null;
        }
        RBNode<K, V> cur = this.root;
        int cmp;
        while (cur != null) {
            cmp = key.compareTo(cur.key);
            if (cmp < 0) {
                cur = cur.left;
            } else if (cmp > 0) {
                cur = cur.right;
            } else {
                return cur;
            }
        }
        // 找不到返回null
        return null;
    }

    /**
     * 根据key获取值
     * @param key key
     * @return    key对应的值
     */
    public V getValue(K key) {
        RBNode<K, V> node = this.root;
        int cmp;
        while (node != null && node.key != key) {
            cmp = key.compareTo(node.key);
            if (cmp < 0) {
                node = node.left;
            } else if (cmp > 0) {
                node = node.right;
            }
        }
        return node == null ? null : node.value;
    }

    public RBNode<K, V> getRoot() {
        return root;
    }
}
