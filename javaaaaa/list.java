import java.util.ArrayList;

import java.util.Stack;

// 栈具有后进先出的特点，在遍历链表时将值按顺序放入栈中，最后出栈的顺序即为逆序。
public class list {
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

        public ListNode(int data) {
            val = data;
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
        start.next = end;// 链接start组和end

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
        while (!stack.isEmpty())
            ret.add(stack.pop());
        return ret;
    }
}
