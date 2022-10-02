import java.io.PushbackInputStream;
import java.util.InputMismatchException;
import javax.print.DocFlavor.INPUT_STREAM;
import javax.sound.sampled.ReverbType;
import javax.swing.plaf.FontUIResource;

public class FrontMiddleBackQueue {

  class Node {

    Node pre, next;
    int val;

    public Node() {}

    public Node(int val) {
      this.val = val;
    }

    public void insertPre(Node node) {
      node.pre = pre;
      node.next = this;
      if (this.pre != null) this.pre.next = node;
      this.pre = node;
    }

    public void insertNext(Node node) {
      node.next = this.next;
      node.pre = this;
      if (this.next != null) this.next.pre = node;
      this.next = node;
    }

    public void deletePre() {
      if (this.pre == null) return;
      Node pointer = this.pre;
      this.pre = pointer.pre;
      if (pointer.pre != null) pointer.pre.next = this;
    }

    public void deleteNext() {
      if (this.next == null) return;
      Node pointer = this.next;
      this.next = pointer.next;
      if (pointer.next != null) pointer.next.pre = this;
    }
  }

  class MyQueue {

    Node dummyHead = new Node(), dummyTail = new Node();
    int count;

    public MyQueue() {
      dummyHead.next = dummyTail;
      dummyHead.pre = null;
      dummyTail.pre = dummyHead;
      dummyTail.next = null;
      count = 0;
    }

    public void pushFront(int value) {
      dummyHead.insertNext(new Node(value));
      count++;
    }

    public void pushBack(int value) {
      dummyTail.insertPre(new Node(value));
      count++;
    }

    public int popBack() {
      if (isEmpty()) return -1;
      int val = dummyTail.pre.val;
      dummyTail.deletePre();
      count--;
      return val;
    }

    public int popFront() {
      if (isEmpty()) return -1;
      int val = dummyHead.next.val;
      dummyHead.deleteNext();
      count--;
      return val;
    }

    public boolean isEmpty() {
      return dummyHead.next == dummyTail;
    }

    public int size() {
      return count;
    }
  }

  MyQueue left = new MyQueue(), right = new MyQueue();

  public FrontMiddleBackQueue() {}

  public void reBalance() {
    if (left.size() < right.size()) {
      left.pushBack(right.popFront());
    }
    if (left.size() == right.size() + 2) {
      right.pushFront(left.popBack());
    }
  }

  public void pushFront(int val) {
    left.pushFront(val);
    reBalance();
  }

  public void pushMiddle(int val) {
    if (left.size() > right.size()) {
      right.pushFront(left.popBack());
    }
    left.pushBack(val);
  }

  public void pushBack(int val) {
    right.pushBack(val);
    reBalance();
  }

  public boolean isEmpty() {
    return left.size() == 0;
  }

  public int popFront() {
    if (isEmpty()) return -1;
    int val = left.popFront();
    reBalance();
    return val;
  }

  public int popMIddle() {
    if (isEmpty()) return -1;
    int val = left.popBack();
    reBalance();
    return val;
  }

  public int popBack() {
    if (isEmpty()) return -1;
    int val;
    if (right.isEmpty()) {
      val = left.popBack();
    } else {
      val = right.popBack();
    }
    reBalance();
    return val;
  }
}
