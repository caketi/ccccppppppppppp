import java.util.*;
import java.util.concurrent.Semaphore;
class ju{
  public int longestSubarray(int[] nums, int limits){
    Deque<Integer> queMax = new ArrayDeque<>();
    Deque<Integer> queMin =  new ArrayDeque<>();
    int n = nums.length;
    int left = 0, right = 0;
    int ret = 0;
    while(right < n){
      while(!queMax.isEmpty() && queMax.peekLast() < nums[right]){
        queMax.pollLast();
      }
      while(!queMin.isEmpty() && queMin.peekLast() > nums[right]){
        queMin.pollLast();
      }
      queMax.offerLast(nums[right]);
      queMin.offerLast(nums[right]);
      while(!queMax.isEmpty()&& !queMin.isEmpty() && queMax.peekFirst() - queMin.peekFirst() > limits){
        if(nums[left] == queMax.peekFirst()){
          queMax.pollFirst();
        }
        if(nums[left] == queMin.peekFirst()){
          queMin.pollFirst();
        }
        left++;
      }
      ret = Math.max(right-left+1, ret);
      right++;
    }
    return ret;
  }
  // 852. 和至少为k的最短子数组
  public int shortestSubarray(int[] nums, int k){
    long[] arr = new long[nums.length + 1];
    for(int i = 0; i < nums.length; i++){
      arr[i+1] = arr[i] + nums[i];
      if(nums[i] == k) return 1;
    }
    int res = Integer.MAX_VALUE;
    Deque<Integer> deque = new ArrayDeque<>();
    for(int i = 0; i<arr.length;i++){
      while(!deque.isEmpty() && arr[i] <= arr[deque.getLast()]){
        deque.removeLast();
      }
      while(!deque.isEmpty() && arr[i] - arr[deque.peekFirst()] >= k){
        res = Math.min(res, i-deque.pollFirst());
      }
      deque.add(i);
    }
    return res == Integer.MAX_VALUE ? -1 : res;
  }
  public int jumpV1(int[] nums){
    Queue<Integer> queue = new ArrayDeque<>();
    int n  = nums.length;
    int ans = 0;
    boolean[] visited = new boolean[n];
    visited[0] = true;
    queue.offer(0);
    while(!queue.isEmpty()){
      int size = queue.size();
      while(size-- >0){
        int idx = queue.poll();
        if(idx == n -1) return ans;
        for(int i = idx + 1; i <= idx+nums[idx] && i < n; i++){
          if(!visited[i]){
            visited[i] = true;
            queue.offer(i);
          }
        }
      }
      ans++;
    }
    return ans;
  }
  public int jump(int[] nums){
    if(nums.length == 1) return 0;
    int start = 0; //起点
    int end = nums[0]; //最远距离
    int ans = 1;
    while(end < nums.length -1 ){
      int tmp = 0; //以当前范围内的位置为起点，下次起跳的最远距离
      for(int i  = start+1; i <= end; i++){
        tmp = Math.max(tmp, nums[i] + i);
      }
      start = end;
      end = tmp;
      ans++;
    }
    return ans;
  }
}



class MaxQueue{
  Queue<Integer> queue;
  Deque<Integer> deque; //  存储队列中的最大值，单调不减的双端队列

  public MaxQueue(){
    queue = new ArrayDeque<>();
    deque = new ArrayDeque<>();
  }

  public int max_value(){
    return deque.isEmpty() ? -1 : deque.peekFirst();
  }
  public void push_back(int value){
    queue.offer(value);
    while(!deque.isEmpty() && deque.peekLast() < value){
      deque.pollLast();
    }
    deque.offerLast(value);
  }
  public int pop_front(){
    if(queue.isEmpty()) return -1;
    if(queue.peek().equals(deque.peekFirst())){
      deque.pollFirst();
    }
    return queue.poll();
  }
}

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
