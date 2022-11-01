import java.util.*;
import java.util.HashMap;
public class stackqueue {
//创建一个栈-=- 寻找栈顶与右侧元素的关系
  // 一个哈希表-- 记录每个元素与他右侧的第一个比他大的值
  // 2. 遍历nums2将元素入栈
  // 3. 遍历nums1在哈希表中寻找比它大的第一个元素
  public int[] nextGreaterElement(int[] nums1, int[] nums2){
    int len1 = nums1.length;
    int len2 = nums2.length;
    Stack<Integer> stack = new Stack<>();
    Map<Integer, Integer> map = new HashMap<>();
    for(int i = 0; i < len2; i++){
      while(!stack.isEmpty() && stack.peek() < nums2[i]){
        map.put(stack.pop(), nums2[i]);
      }
      stack.push(nums2[i]);
    }
    int[] res = new int[len1];
    for(int i = 0; i < len1; i++){
      res[i] = map.getOrDefault(nums1[i], -1);
    }
    return res;
  }
  public int[] nextGreaterElementsV2(int[] nums){
    int n = nums.length;
    int[] ans = new int[n];
    Arrays.fill(ans, -1);
    Stack<Integer> stack = new Stack<>();
    for(int i = 0; i < n * 2; i++){
      while(!stack.isEmpty() && nums[i%n] > nums[stack.peek()]){
        int u = stack.pop();
        ans[u] = nums[i%n];
      }
      stack.push(i%n);
    }
    return ans;
  }
  public int[] nextGreaterElementsV3(int[] nums){
    int n = nums.length;
    int[] ans = new int[n];
    for(int i = n - 1; i > 0; i--){
      if(nums[i-1] >= nums[i]){
        ans[i-1] = ans[i];
      }else {
        ans[i-1] = i;
      }
    }
    for(int i  = 0; i < n; i++){
      int element = nums[i];
      int j = ans[i];
      ans[i] = -1;
      do{
        if(nums[j] > element){
          ans[i] = nums[j];
          break;
        }
        j++;
        if(j >= n){
          j -= n;
        }
      }while(j != 1);
    }
    return ans;
  }
  public int[] dailyTemperatures(int[] temperatures){
    int len = temperatures.length;
    int[] res = new int[len];
    Stack<Integer> stack = new Stack<>();
    for(int i = 0; i<len; i++){
      int cur = temperatures[i];
      while(!stack.isEmpty()&& cur > temperatures[stack.peek()]){
        int idx = stack.pop();
        res[idx] = i - idx;
      }
      stack.push(i);
    }
    return res;
  }
  class StockSpanner{
    Stack<Integer> days, prices;
    public StockSpanner(){
      // 股票每天的跨度天数
      days = new Stack<>();
      prices = new Stack<>();
      // 股票每天的价格
    }
    public int next(int price){
      int day = 1;
      while(!prices.isEmpty()&& prices.peek() <= price){
        prices.pop();
        day += days.pop();
      }
      prices.push(price);
      days.push(day);
      return day;
    }
  }
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
