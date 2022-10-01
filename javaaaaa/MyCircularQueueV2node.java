import javax.swing.plaf.basic.BasicTreeUI.TreeCancelEditingAction;

public class MyCircularQueueV2node {
    class Node {
        int value;
        Node nextNode;

        public Node(int value) {
            this.value = value;
        }
    }

    Node head, tail;
    int count, capacity;

    public MyCircularQueueV2node(int k) {
        capacity = k;
    }

    public boolean enQueue(int value) {
        if (count == capacity)
            return false;
        Node newNode = new Node(value);
        if (count == 0) {
            head = tail = newNode;
        } else {
            tail.nextNode = newNode;
            tail = newNode;
        }
        count++;
        return true;
    }

    public boolean deQueue() {
        if (count == 0)
            return false;
        head = head.nextNode;
        count--;
        return true;
    }

    public int Front() {
        if (count == 0)
            return -1;
        return head.value;
    }

    public int Rear() {
        if (count == 0)
            return -1;
        return tail.value;
    }

    public boolean isEmpty() {
        return count == 0;
    }

    public boolean isFull() {
        return count == capacity;
    }

}
