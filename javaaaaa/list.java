import java.util.*;

// 栈具有后进先出的特点，在遍历链表时将值按顺序放入栈中，最后出栈的顺序即为逆序。
public class list {
  // H x 链表头插入一个数x
  // D k 删除第k个插入的数后面的数（k==0）删除头结点
  // I k x 在k个插入的数后面插入一个数x k大于0
  class LinkedListArray{
    static int[] e = new int[100001]; //存val
    static int[] ne = new int[1000001]; //存next
    static int head, idx;
    public static void main(String[] args){
      Scanner sca = new Scanner(System.in);
      int m = sca.nextInt();
      
      init();
      while(m -- > 0){
        char opt = sca.next().charAt(0);
        if(opt == 'H'){
          int x = sca.nextInt();
          addHead(x);
        }else if(opt == 'D'){
          int k = sca.nextInt();
          if(k == 0) head = ne[head];
          else remove(k-1);
        }else {
          int k = sca.nextInt();
          int x = sca.nextInt();
          insert(k-1, x);
        }
      }
    }
    public static void init(){
      head = -1;
      idx = 0;
    }
    public static void addHead(int x){
      e[idx] = x;
      ne[idx] = head;
      head = idx;
      idx++;
    }
    public static void insert(int k , int x){
      e[idx] = x;
      ne[idx] = ne[k];
      ne[k] = idx;
      idx++;
    }
    public static void remove(int k){
      ne[k] = ne[ne[k]];
    }
  }
  // L x -- 在链表最左端插入x || R x 
  // D k --将第k个插入的数删除
  // IL k x -- 在第k个插入的数左侧插入一个数 || IR k x
  class doubleLinkedListArray{
    static int[] e = new int[10003];
    static int[] le = new int[10003];
    static int[] re = new int[10003];
    static int ids;
    public static void main(String[] args){
      Scanner sca = new Scanner(System.in);
      int m = sca.nextInt();
      init();
      while(m-- > 0){
        String opt = sca.next();
        if(opt.equals("D")){
          int k = sca.nextInt();
          remove(k+1);
        }else if(opt.equals("L")){
          int x = sca.nextInt();
          add(0,x);
        }else if(opt.equals("R")){
          int x = sca.nextInt();
          add(le[1], x);
        }else if(opt.equals("IL")){
          int k = sca.nextInt();
          int x = sca.nextInt();
          add(le[k+1], x);
        }else {
          int k = sca.nextInt();
          int x = sca.nextInt();
          add(k+1, x);
        }
      }
      for(int i = re[0]; i != 1; i = re[i]){
        System.out.println(e[i] + " ");
      }
    }
    public static void init(){
      re[0] = 1; // 0的右边1
      le[1] = 0; // 1的左边0
      ids = 2;  // 已插入2
    }
    public static void add(int k, int x){
      e[ids] = x; //第ids个数是x
      re[ids] = re[k]; // x的右边就是k的右边
      le[ids] = k; //x的左边就是k
      le[re[k]] = ids; // k的右边的左边就是x
      re[k] = ids; // k的右就是x
      ids++; // 已有的数++ 多了一个数
    }
    public static void remove(int k){
      re[le[k]] = re[k]; // 删除一个数，把它的左右链接断掉，跳过就行
      le[re[k]] = le[k];
    }
  }

  // class ListNode<E> {
  // private ListNode<E> pre;
  // private ListNode<E> next;
  // }
  // class LinkedList<E>{
  // private ListNode<E> head;
  // private ListNode<E> tail;
  // private int size;

  // }

  public static void main(String[] args) {
    // List<Integer> list = new ArrayList<Integer>();

    // System.out.println(list.size());
    // list.add(1);
    // System.out.println(list.size());

    // list.add(0,2);// add at head
    // System.out.println(list.size());
    // list.add(1,3); // add at middle
    // System.out.println(list.get(1));
    // list.remove(1);
    // list.set(0, 4);
    // System.out.println(list);

    // for(int i = 10; i <= 20; i++){
    // list.add(i);
    // }
    // System.out.println(list);

    // for(int i = 0; i<5; i++){
    // list.remove(list.size()-1);
    // }
    // System.out.println(list);
    // for(int i : list){
    // list.remove(); // ConcurrentModificationException
    // }
    // ArrayList<Integer> lista = null;
    // NullPointerException: Cannot invoke "java.util.ArrayList.isEmpty()" because
    // "lista" is null
    // if(!lista.isEmpty()){
    // System.out.println(lista.size());
    // }
    // System.out.println(lista.get(0));

    // ArrayList<Integer> list = new ArrayList<>();
    // if(list.isEmpty()){
    // System.out.println(list.size());
    // }
    // System.out.println(list.get(0)); // IndexOutOfBoundsException
    // 不同 null---no array object associated with reference
    // empty arraylist - there is an arraylist object, but the arraylist object dont
    // contain any element
    // size/lenght == 0
    // int[] array = null;
    // int[] array1 = new int[0];

    // ArrayList<Integer> list1ArrayList = null;
    // ArrayList<Integer> list2ArrayList = new ArrayList<Integer>();

  }

  public static class Node {

    public int value;
    public Node next;

    public Node(int data) {
      value = data;
    }
  }

  public static class DoubleNode {

    public int value;
    public DoubleNode last;
    public DoubleNode next;

    public DoubleNode(int data) {
      value = data;
    }
  }

  public static Node reverseLinkedList(Node head) {
    Node pre = null;
    Node next = null;
    while (head != null) {
      next = head.next;

      head.next = pre;
      pre = head;
      head = next;
    }
    return pre;
  }

  public static DoubleNode reverseDoubleLinkedList(DoubleNode head) {
    DoubleNode pre = null;
    DoubleNode next = null;
    while (head != null) {
      next = head.next;

      head.next = pre;
      head.last = next;
      pre = head;
      head = next;
    }
    return pre;
  }

  public static class ListNode {

    public int val;
    public ListNode next;
    public ListNode random;

    public ListNode() {}

    public ListNode(int data) {
      val = data;
    }

    public ListNode(int val, ListNode next) {
      this.val = val;
      this.next = next;
    }
  }

  public ListNode remove(ListNode head, int value) {
    if (head == null) {
      return null;
    } else if (head.val == value) {
      return head.next;
    }
    ListNode cur = head;
    while (cur.next != null && cur.next.val != value) {
      cur = cur.next;
    }
    // cur.next == null || cur.next.val == value;
    if (cur.next != null) {
      cur.next = cur.next.next;
    }
    return head;
  }

  public ListNode mid(ListNode head) {
    if (head == null) {
      return head;
    }
    ListNode slow = head;
    ListNode fast = head;
    while (fast.next != null && fast.next.next != null) {
      slow = slow.next;
      fast = fast.next.next;
    }
    return slow;
  }

  public ListNode insert(ListNode head, int val) {
    ListNode dummy = new ListNode(0);
    dummy.next = head;
    // insert 0
    // dummy->0->1->3->5
    ListNode newNode = new ListNode(val);
    ListNode curr = dummy.next, prev = dummy;
    while (curr != null && curr.val < val) {
      prev = curr;
      curr = curr.next;
    }
    prev.next = newNode;
    newNode.next = curr;
    return dummy.next;
  }

  public static ListNode mergeTwoLists(ListNode head1, ListNode head2) {
    if (head1 == null || head2 == null) {
      return head1 == null ? head2 : head1;
    }
    ListNode head = head1.val <= head2.val ? head1 : head2;
    ListNode cur1 = head.next;
    ListNode cur2 = head == head1 ? head2 : head1;
    ListNode pre = head;
    while (cur1 != null && cur2 != null) {
      if (cur1.val <= cur2.val) {
        pre.next = cur1;
        cur1 = cur1.next;
      } else {
        pre.next = cur2;
        cur2 = cur2.next;
      }
      pre = pre.next;
    }
    pre.next = cur1 != null ? cur1 : cur2;
    return head;
  }

  public static int listLength(ListNode head) {
    int len = 0;
    while (head != null) {
      len++;
      head = head.next;
      // len++;
    }
    return len;
  }

  // 4->3->6 634+352 = 986
  // 2->5->3
  // 6->8->9
  public static ListNode addTwoNumbers(ListNode head1, ListNode head2) {
    int len1 = listLength(head1);
    int len2 = listLength(head2);

    ListNode l = len1 >= len2 ? head1 : head2;
    ListNode s = l == head1 ? head2 : head1;

    ListNode curL = l;
    ListNode curS = s;
    ListNode last = curL; // 幽灵跟踪
    int carry = 0;
    int curNum = 0;
    while (curS != null) {
      curNum = curL.val + curS.val + carry;
      curL.val = (curNum % 10);
      carry = curNum / 10;
      last = curL;
      curL = curL.next;
      curS = curS.next;
    }
    while (curL != null) {
      curNum = curL.val + carry;
      curL.val = (curNum % 10);
      carry = curNum / 10;
      last = curL;
      curL = curL.next;
    }
    if (carry != 0) {
      last.next = new ListNode(1);
    }
    return l;
  }

  public ListNode addTwoNumbersV2(ListNode l1, ListNode l2) {
    LinkedList<Integer> stack1 = new LinkedList<>();
    LinkedList<Integer> stack2 = new LinkedList<>();

    while (l1 != null) {
      stack1.push(l1.val);
      l1 = l1.next;
    }
    while (l2 != null) {
      stack2.push(l2.val);
      l2 = l2.next;
    }
    int tmp = 0;
    ListNode result = null;
    while (!stack1.isEmpty() || !stack2.isEmpty() || tmp != 0) {
      int a = stack1.isEmpty() ? 0 : stack1.pop();
      int b = stack2.isEmpty() ? 0 : stack2.pop();
      int cur = a + b + tmp;
      tmp = cur / 10; //进位
      cur %= 10; // 个位
      ListNode curNode = new ListNode(cur);
      curNode.next = result; //头插
      result = curNode;
    }
    return result;
  }

  public static ListNode reverseKGroup(ListNode head, int k) {
    ListNode start = head;
    ListNode end = getKGroupEnd(start, k);
    if (end == null) {
      return head;
    }
    // 第一组凑齐
    head = end;
    reverse(start, end);
    // 上一组的结尾节点
    ListNode lastEnd = start;
    while (lastEnd.next != null) {
      start = lastEnd.next;
      end = getKGroupEnd(start, k);
      if (end == null) {
        return head;
      }
      reverse(start, end);
      lastEnd.next = end;

      lastEnd = start;
    }
    return head;
  }

  public static ListNode getKGroupEnd(ListNode start, int k) {
    while (--k != 0 && start != null) {
      start = start.next;
    }
    return start;
  }

  public static void reverse(ListNode start, ListNode end) {
    end = end.next;
    ListNode pre = null;
    ListNode cur = start;
    ListNode next = null;
    while (cur != end) {
      next = cur.next;

      cur.next = pre;
      pre = cur;
      cur = next;
    }
    start.next = end; // 链接start组和end
  }

  // pre curr next
  public ListNode reverseList(ListNode head) {
    ListNode pre = null, curr = head, next = null;
    while (curr != null) {
      next = curr.next;
      curr.next = pre;
      pre = curr;
      curr = next;
    }
    return pre;
  }

  public ListNode reverseBetweenV2(ListNode head, int left, int right) {
    ListNode hair = new ListNode(0, head), con = hair, tail = null;
    int n = right - left + 1;
    while (left > 1) {
      con = con.next;
      left--;
    }
    con.next = reverse(con.next, n); // 头连接反转后的头
    return hair.next;
  }

  // 找到m的前一个节点
  public ListNode reverse(ListNode head, int n) {
    ListNode pre = new ListNode(), curr = head, next = null;
    while (n > 0) {
      next = curr.next;
      curr.next = pre.next; // curr指向反转
      pre.next = curr;
      curr = next;
      n--;
    }
    head.next = curr; // 连接反转后的尾巴和原来链表的下一段
    return pre.next; // 返回反转后的头 pre永远守护反转后的头（pre骑士团）
  }

  public ArrayList<Integer> printListFromTailToHead1(ListNode listNode) {
    ArrayList<Integer> ret = new ArrayList<>();
    if (listNode != null) {
      ret.addAll(printListFromTailToHead(listNode.next));
      ret.add(listNode.val);
    }
    return ret;
  }

  // node3 = node1.next;
  // node2.next = node3;
  // node1.next = node2;
  public ArrayList<Integer> printListFromTailToHead2(ListNode listNode) {
    // 头插法构建逆序链表
    ListNode head = new ListNode(-1);
    while (listNode != null) { // listnode
      // head head.next
      ListNode memo = listNode.next;
      listNode.next = head.next;
      head.next = listNode;
      listNode = memo; // 下一个
    }
    // 构建 ArrayList
    ArrayList<Integer> ret = new ArrayList<>();
    head = head.next;
    while (head != null) {
      ret.add(head.val);
      head = head.next;
    }
    return ret;
  }

  public ArrayList<Integer> printListFromTailToHead(ListNode listNode) {
    Stack<Integer> stack = new Stack<>();
    while (listNode != null) {
      stack.add(listNode.val);
      listNode = listNode.next;
    }
    ArrayList<Integer> ret = new ArrayList<>();
    while (!stack.isEmpty()) ret.add(stack.pop());
    return ret;
  }

  public ListNode detectCycle(ListNode head) {
    if (head == null) return null;
    ListNode fast = head, slow = head;
    do {
      if (fast == null || fast.next == null) {
        return null;
      }
      fast = fast.next.next;
      slow = slow.next;
    } while (fast != slow);
    fast = head;
    while (fast != head) {
      slow = slow.next;
      fast = fast.next;
    }
    return fast;
  }

  public boolean hasCycle(ListNode head) {
    HashSet<ListNode> hashSet = new HashSet<ListNode>();
    while (head != null) {
      if (!hashSet.add(head)) { // add-返回false--元素存在rue if this set did not already contain the specified
        // element
        return true; // return head;
      }
      head = head.next;
    }

    return false; // return null
  }

  public boolean hasCycleV2(ListNode head) {
    if (head == null) return false;
    ListNode fast = head, slow = head;
    do {
      if (fast == null || fast.next == null) {
        return false;
      }
      slow = slow.next;
      fast = fast.next.next;
    } while (fast != slow);
    return true;
  }

  // 一个数拆开 平方和看能为1
  public boolean isHappy(int n) {
    int fast = n, slow = n;
    do {
      // if (fast == 1 || getNext(fast) == 1)
      // return true;
      fast = getNext(getNext(fast));
      slow = getNext(slow);
    } while (fast != slow && fast != 1);
    return fast == 1;
  }

  public int getNext(int n) {
    int sum = 0;
    while (n > 0) {
      // 15 ----- 5 * 5
      sum += (n % 10) * (n % 10);
      n = n / 10;
    }
    return sum;
  }

  public ListNode reverseKGroupV2(ListNode head, int k) {
    ListNode hair = new ListNode(0, head), pre = hair, tail = null;
    while (head != null) {
      tail = pre;
      for (int i = 0; i < k; i++) {
        tail = tail.next;
        if (tail == null) {
          return hair.next;
        }
      }
      ListNode[] reverse = reverseV3(head, tail);
      head = reverse[0];
      tail = reverse[1];
      pre.next = head; // 连接
      pre = tail;
      head = pre.next;
    }
    return hair.next;
  }

  public ListNode[] reverseV3(ListNode head, ListNode tail) {
    ListNode pre = tail.next, curr = head, next = null;
    while (pre != tail) {
      next = curr.next;
      curr.next = pre;
      pre = curr;
      curr = next;
    }
    return new ListNode[] { tail, head };
  }

  public ListNode rotateRight(ListNode head, int k) {
    if (head == null || head.next == null) return head;
    int length = 1;
    ListNode oldTail = head;
    while (oldTail.next != null) {
      oldTail = oldTail.next;
      length++;
    }
    oldTail.next = head; // 练成环
    // ListNode newTail = head;
    for (int i = 0; i < length - k % length - 1; i++) {
      // newTail = newTail.next; //找到尾
      // }
      head = head.next;
    }
    // ListNode newHead = newTail.next;
    // newTail.next = null;
    ListNode newHead = head.next;
    head.next = null;
    return newHead;
  }

  public ListNode swapPairs(ListNode head) {
    ListNode hair = new ListNode(0, head), pre = hair;
    while (pre.next != null && pre.next.next != null) {
      ListNode one = pre.next;
      ListNode two = pre.next.next;
      one.next = two.next;
      two.next = one;
      pre.next = two;
      pre = one;
    } // pre--守护
    return hair.next;
  }

  public ListNode removeNthFromEnd(ListNode head, int n) {
    ListNode hair = new ListNode(0, head), fast = head, slow = hair;
    while (n > 0) {
      fast = fast.next;
      n--;
    }
    while (fast != null) {
      slow = slow.next;
      fast = fast.next;
    }
    slow.next = slow.next.next;
    return hair.next;
  }

  public ListNode deleteDuplicates(ListNode head) {
    ListNode curr = head;
    while (curr != null && curr.next != null) {
      if (curr.val == curr.next.val) {
        curr.next = curr.next.next;
      } else {
        curr = curr.next;
      }
    }
    return head;
  }

  public ListNode deleteDuplicatesV2(ListNode head) {
    ListNode hair = new ListNode(0, head), pre = hair, curr = head;
    while (curr != null) {
      while (curr.next != null && curr.val == curr.next.val) {
        curr = curr.next;
      }
      if (pre.next == curr) {
        pre = pre.next;
      } else {
        pre.next = curr.next;
      }
      curr = curr.next;
    }
    return hair.next;
  }

  // small链表 big链表 big链表尾巴滞空，small链表尾巴连接big头，返回small头
  public ListNode partitionSmallAndBig(ListNode head, int x) {
    ListNode small = new ListNode(0);
    ListNode big = new ListNode(0);
    ListNode smallHair = small;
    ListNode bigHair = big;
    while (head != null) {
      if (head.val < x) {
        small.next = head;
        small = small.next;
      } else {
        big.next = head;
        big = big.next;
      }
      head = head.next;
    }
    big.next = null;
    small.next = bigHair.next;
    return smallHair.next;
  }

  public int getListLen(ListNode root) {
    int len = 0;
    while (root != null) {
      ++len;
      root = root.next;
    }
    return len;
  }
  public ListNode[] splitListToParts(ListNode root, int k){
    ListNode left, right;
    List<Object> result = new ArrayList<>();
    int listLen = getListLen(root);
    for(int i = 0, len; i < k; i++){
        result.add(root);
        len = i<(listLen % k) ? listLen / k+1 : listLen / k;
        right = root;
        while(--len > 0){
            right = right.next;
        }
        left = null;
        while(right!=null){
            left = right.next; //走到夏一部分
            right.next = null; //断开链接，分隔
        }
        root = left; // 开始新的分隔
    }
    return result.toArray(new ListNode[0]);
  }
//   1->2->3->4 ------ 1->4->2->3
  public void reorderList(ListNode head){
    if(head == null) return;
    List<ListNode> list = new ArrayList<>();
    ListNode node =head;
    while(node != null){
        list.add(node);
        node = node.next;
    }
    int i = 0, j = list.size()- 1;
    while(i < j){
        list.get(i).next = list.get(j);
        i++;
        if(i==j)break;
        list.get(j).next = list.get(i);
        j--;
    }
    list.get(i).next = null;
  }
  public ListNode copyRandomList(ListNode head) {
    if (head == null) return null;
    ListNode pointer = head;
    while (pointer != null) {
      ListNode newNode = new ListNode(pointer.val);
      newNode.next = pointer.next;
      pointer.next = newNode; // 复制节点
      pointer = newNode.next; // 指向下一个待复制的节点
    }
    pointer = head;
    while (pointer != null) {
      pointer.next.random =
        (pointer.random != null) ? pointer.random.next : null;
      pointer = pointer.next.next; // 复制random，跳向下一个
    }
    ListNode pointerOldList = head;
    ListNode pointerNewList = head.next;
    ListNode newHead = head.next;
    while (pointerOldList != null) {
      pointerOldList.next = pointerOldList.next.next;
      pointerNewList.next =
        (pointerNewList.next != null) ? pointerNewList.next.next : null;
      pointerOldList = pointerOldList.next;
      pointerNewList = pointerNewList.next;
    }
    return newHead;
  }
}
