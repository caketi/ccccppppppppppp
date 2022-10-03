import java.util.Stack;

class calPoint {

  public int calPoints(String[] ops) {
    Stack<Integer> stack = new Stack<>();
    for (String op : ops) {
      if (op.equals("+")) {
        int a = stack.pop();
        int b = stack.peek() + a;
        stack.push(a);
        stack.push(b);
      } else if (op.equals("D")) {
        stack.push(2 * stack.peek());
      } else if (op.equals("C")) {
        stack.pop();
      } else {
        stack.push(Integer.parseInt(op));
      }
    }
    int res = 0;
    for (Integer integer : stack) {
      res += integer;
    }
    return res;
  }
}

class MyQueue {

  Stack<Integer> inStack = new Stack();
  Stack<Integer> outStack = new Stack();

  MyQueue() {}

  public void push(int x) {
    inStack.push(x);
  }

  public void transfer() {
    if (!outStack.isEmpty()) return;
    while (!inStack.isEmpty()) {
      outStack.push(inStack.pop());
    }
  }

  public int pop() {
    transfer();
    return outStack.pop();
  }

  public int peek() {
    transfer();
    return outStack.peek();
  }

  public boolean empty() {
    return outStack.empty() && inStack.empty();
  }
}

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
    if (count == capacity) return false;
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
    if (count == 0) return false;
    head = head.nextNode;
    count--;
    return true;
  }

  public int Front() {
    if (count == 0) return -1;
    return head.value;
  }

  public int Rear() {
    if (count == 0) return -1;
    return tail.value;
  }

  public boolean isEmpty() {
    return count == 0;
  }

  public boolean isFull() {
    return count == capacity;
  }
}
