import java.util.ArrayList;
import java.util.Deque;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Stack;

public class stackqueue {

  
// 1021删除最外层括号
  public String minRemoveToMakeValid2(String s) {
    StringBuilder stringBuilder = new StringBuilder(s);
    Deque<Integer> stack = new LinkedList<>();
    for (int i = 0; i < s.length(); i++) {
      if (s.charAt(i) == '(') {
        stack.push(i);
      } else if (s.charAt(i) == ')') {
        if (!stack.isEmpty() && s.charAt(stack.peek()) == '(') {
          stack.pop();
        } else stack.push(i);
      }
    }
    for (Integer integer : stack) {
      stringBuilder.deleteCharAt(integer);
    }
    return stringBuilder.toString();
  }

  public String minRemoveToMakeValid(String s) {
    char[] t = new char[s.length()];
    char[] ans = new char[s.length()];
    int tlen = 0;
    for (int i = 0, cnt = 0; i < s.length(); i++) {
      if (s.charAt(i) == '(' || s.charAt(i) != ')') {
        if (s.charAt(i) == '(') cnt++;
        t[tlen++] = s.charAt(i);
      } else {
        if (cnt == 0) continue;
        cnt--;
        t[tlen++] = ')';
      }
    }
    int ansHead = tlen;
    for (int i = tlen - 1, cnt = 0; i >= 0; i--) {
      if (t[i] == ')' || t[i] != '(') {
        if (t[i] == ')') cnt++;
        ans[--ansHead] = t[i];
      } else {
        if (cnt == 0) continue;
        cnt--;
        ans[--ansHead] = '(';
      }
    }
    return new String(ans).trim();
  }

  public String removeOuterParentheseV2(String S) {
    StringBuilder sb = new StringBuilder();
    int level = 0;
    for (char c : S.toCharArray()) {
      if (c == ')') --level;
      if (level >= 1) sb.append(c);
      if (c == '(') ++level;
    }
    return sb.toString();
  }

  public String removeOuterParenthese(String S) {
    StringBuilder stringBuilder = new StringBuilder();
    int pre = 0, count = 0;
    for (int i = 0; i < S.length(); i++) {
      if (S.charAt(i) == '(') {
        count++;
      } else {
        count--;
      }
      if (count != 0) {
        continue;
      } else {
        stringBuilder.append(S.substring(pre + 1, i)); //前闭后开
        pre = i + 1;
      }
    }
    return stringBuilder.toString();
  }

  public boolean isValid(String s) {
    HashMap<Character, Character> map = new HashMap<>();
    map.put(')', '(');
    map.put(']', '[');
    map.put('}', '{');
    Stack<Character> stack = new Stack<>();
    for (int i = 0; i < s.length(); i++) {
      switch (s.charAt(i)) {
        case '(':
        case '[':
        case '{':
          stack.push(s.charAt(i));
          break;
        case ')':
        case '}':
        case ']':
          if (
            stack.isEmpty() || map.get(s.charAt(i)) != stack.peek()
          ) return false;
          stack.pop();
          break;
      }
    }
    return stack.isEmpty();
  }

  public boolean validateStackSequences(int[] pushed, int[] popped) {
    Stack<Integer> stack = new Stack<>();
    int j = 0;
    for (int n : pushed) {
      stack.push(n);
      while (!stack.empty() && j < popped.length && stack.peek() == popped[j]) {
        stack.pop();
        j++;
      }
    }
    return stack.isEmpty();
  }

  public stackqueue() {}

  public static class Node<V> {

    public V value;
    public Node<V> last;
    public Node<V> next;

    public Node(V v) {
      value = v;
      last = null;
      next = null;
    }
  }

  public static class MyDeque<V> {

    private Node<V> head;
    private Node<V> tail;
    private int size;

    public MyDeque() {
      head = null;
      tail = null;
      size = 0;
    }

    public boolean isEmpty() {
      return size == 0;
    }

    public int size() {
      return size;
    }

    public void pushHead(V value) {
      Node<V> cur = new Node<>(value);
      if (head == null) {
        head = cur;
        tail = cur;
      } else {
        cur.next = head;
        head.last = cur;
        head = cur;
      }
      size++;
    }

    public void pushTail(V value) {
      Node<V> cur = new Node<>(value);
      if (head == null) {
        head = cur;
        tail = cur;
      } else {
        tail.next = cur;
        cur.last = tail;
        tail = cur;
      }
    }

    public V pollHead() {
      V ans = null;
      if (head == null) {
        return ans;
      }
      size--;
      ans = head.value;
      if (head == tail) {
        head = null;
        tail = null;
      } else {
        head = head.next;
        head.last = null;
      }
      return ans;
    }

    public V pollTail() {
      V ans = null;
      if (head == null) {
        return ans;
      }
      size--;
      ans = tail.value;
      if (head == tail) {
        head = null;
        tail = null;
      } else {
        tail = tail.last;
        tail.next = null;
      }
      return ans;
    }
  }
}
