import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.Deque;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.PriorityQueue;
 
class MyProqu{
  public  int[] hp = new int[100010];
  public  int size = 0;

  public  void swap(int x, int y){
    int temp = hp[x];
    hp[x] = hp[y];
    hp[y] = temp;
  }
  public  void offer(int x){
    hp[size++] = x;
    int child = size - 1;
    int p = child /2 ;
    while(p >= 0){
      if(hp[p] < hp[child]){
        swap(p, child);
        child = p;
        p = child/2;
      }else {
        break;
      }
    }
  }
  public static void main(String[] args){
    MyProqu mq = new MyProqu();
    mq.offer(1);
    mq.offer(2);
    mq.offer(3);
    for(int i = 0; i<mq.size;i++){
      System.out.println(mq.hp[i]);
    }
  }
}

class MyHeap {

  public int[] hp = new int[10];
  public int size = 0;

  private void swap(int x, int y) {
    int temp = y;
    y = x;
    x = temp;
  }

  private void shiftDown(int p, int size) {
    int child = (p + 1) * 2;
    // 
    while (child < size) {
      if (child + 1 < size && hp[child] > hp[child + 1]) child++;
      if (hp[p] > hp[child]) {
        swap(hp[p], hp[child]);
        p = child;
        child = (p + 1) * 2;
      } else {
        break;
      }
    }
  }

  public void createHeap() {
    for (int i = 9; i >= 0; i--) {
      hp[i] = i;
     
      size++;
    }
    for (int p = (size - 2 / 2); p >= 0; p--) {
      shiftDown(p, size);
    }
  }

  public static void main(String[] args) {
    MyHeap hp = new MyHeap();
    hp.createHeap();
    for (int x : hp.hp) {
      System.out.print(x + " ");
    }
  }
}

class heapi {
  public static void main(String[] args){
    int[] test = {1,3,-1,-3,5,3,6,7};
    int[] ans = maxSlidingWindowV2(test, 3);
    for(int res : ans){
      System.out.print(res+" ");
    }
  }
  // [1,3,-1,-3,5,3,6,7], k=3
  public static int[] maxSlidingWindowV2(int[] nums, int k){
    int n = nums.length;
    Deque<Integer> deque = new ArrayDeque<>();
    for(int i = 0; i < k; i++){
      while(!deque.isEmpty() && nums[i] > nums[deque.peekLast()]){
        deque.pollLast(); //队列不空，比较不断，小的踢出去，大的走进来！
      }
      deque.offerLast(i);
    }
    int[] ans = new int[n-k+1];
    ans[0] = nums[deque.peekFirst()];
    for(int i = k ;i < n; i++){
      while(!deque.isEmpty() && nums[i] > nums[deque.peekLast()]){
        deque.pollLast(); //队列不空，比较不断，小的踢出去，大的走进来！
      }
      deque.offer(i);
      while(deque.peekFirst() <= i- k){ //出了滑动窗口范围
        deque.pollFirst();
      }
      ans[i-k+1] = nums[deque.peekFirst()];
    }
    return ans;
  }
  public int[] maxSlidingWindow(int[] nums, int k){
    int n = nums.length;
    PriorityQueue<int[]> pq = new PriorityQueue<>(new Comparator<int[]>(){
      public int compare(int[] o1, int[] o2){
        return o1[0] != o2[0] ? o2[0] - o1[0] : o2[1] - o1[1];
      }
    });
    for(int i = 0; i< n; i++){
      pq.offer(new int[]{nums[i], i});
    }
    int[] ans = new int[n-k+1];
    ans[0] = pq.peek()[0];
    for(int i = k; i < n; i++){
      pq.offer(new int[]{nums[i], i});
      while(pq.peek()[1] <= i-k){ //出了滑动窗口范围
        pq.poll();
      }
      ans[i-k+1] = pq.peek()[0];
    }
    return ans;
  }
  public int[] getLeastNumbers(int[] arr, int k) {
    PriorityQueue<Integer> priorityQueue = new PriorityQueue<>(); //小顶堆
    for (int i : arr) {
      priorityQueue.offer(i);
    }
    int[] result = new int[k];
    for (int i = 0; i < k; i++) {
      result[i] = priorityQueue.poll(); //弹出会平衡
    }
    return result;
  }

  public int[] getLeastNumbersV2(int[] arr, int k) {
    PriorityQueue<Integer> priorityQueue = new PriorityQueue<>(
      (o1, o2) -> o2 - o1
    );
    for (int i : arr) {
      priorityQueue.offer(i);
      if (priorityQueue.size() > k) priorityQueue.poll(); //最小的k个数，多的踢掉，堆顶最大
    }
    // for(int i = 0; i < k; i++){
    //   priorityQueue.offer(arr[i]);
    // }
    // for(int i = k; i < arr.length; i++){
    //   if(arr[i] < priorityQueue.peek()){
    //     priorityQueue.poll();
    //     priorityQueue.offer(arr[i]);
    //   }
    // }
    return priorityQueue.stream().mapToInt(i -> i).toArray();
  }

  public int lastStoneWeight(int[] stones) {
    PriorityQueue<Integer> priorityQueue = new PriorityQueue<>(
      (o1, o2) -> o2 - o1
    );
    for (int stone : stones) {
      priorityQueue.offer(stone);
    }
    while (priorityQueue.size() > 1) {
      int x = priorityQueue.poll();
      int y = priorityQueue.poll();
      if (x > y) {
        priorityQueue.offer(Math.abs(x - y));
      }
    }
    return priorityQueue.isEmpty() ? 0 : priorityQueue.poll();
  }

  public List<List<Integer>> KSmallestPairs(int[] nums1, int[] nums2, int k) {
    PriorityQueue<int[]> priorityQueue = new PriorityQueue<>(
      (int[] o1, int[] o2) -> o2[2] - o1[2]
    );
    for (int i = 0; i < nums1.length; i++) {
      for (int j = 0; j < nums2.length; j++) {
        if (
          priorityQueue.size() < k ||
          (nums1[i] + nums2[j]) < priorityQueue.peek()[2]
        ) {
          priorityQueue.offer(
            new int[] { nums1[i], nums2[j], nums1[i] + nums2[j] }
          );
          if (priorityQueue.size() > k) priorityQueue.poll();
        } else break;
      }
    }

    List<List<Integer>> result = new ArrayList<>();
    while (!priorityQueue.isEmpty()) {
      int[] ints = priorityQueue.poll();
      result.add(
        new ArrayList<Integer>() {
          {
            this.add(ints[0]);
            this.add(ints[1]);
          }
        }
      );
    }
    return result;
  }

  public List<List<Integer>> kSmallestPairs(int[] nums1, int[] nums2, int k) {
    PriorityQueue<Integer[]> priorityQueue = new PriorityQueue<>(
      (Integer[] o1, Integer[] o2) -> (o2[0] + o2[1]) - (o1[0] + o1[1])
    );
    for (int i = 0; i < nums1.length; i++) {
      for (int j = 0; j < nums2.length; j++) {
        priorityQueue.offer(new Integer[] { nums1[i], nums2[j] });
        if (priorityQueue.size() > k) priorityQueue.poll();
      }
    }
    List<List<Integer>> result = new ArrayList<>();
    while (!priorityQueue.isEmpty()) {
      result.add(Arrays.asList(priorityQueue.poll()));
    }
    return result;
  }

  public List<String> topKFrequent(String[] words, int k) {
    HashMap<String, Integer> map = new HashMap<>();
    for (String word : words) {
      map.put(word, map.getOrDefault(word, 0) + 1);
    }
    PriorityQueue<Map.Entry<String, Integer>> priorityQueue = new PriorityQueue<>(
      new Comparator<Map.Entry<String, Integer>>() {
        public int compare(
          Map.Entry<String, Integer> o1,
          Map.Entry<String, Integer> o2
        ) {
          return o1.getValue() == o2.getValue()
            ? o2.getKey().compareTo(o1.getKey())
            : o1.getValue() - o2.getValue();
        }
      }
    );
    for (Map.Entry<String, Integer> entry : map.entrySet()) {
      priorityQueue.offer(entry);
      if (priorityQueue.size() > k) priorityQueue.poll();
    }
    List<String> result = new ArrayList<>();
    while (!priorityQueue.isEmpty()) {
      result.add(0, priorityQueue.poll().getKey());
    }
    return result;
  }

  class MedianFinder {

    PriorityQueue<Integer> smallHeap;
    PriorityQueue<Integer> bigHeap;

    //bigHeap放小数 smallHeap放大数
    public MedianFinder() {
      smallHeap = new PriorityQueue<>();
      bigHeap = new PriorityQueue<>((o1, o2) -> o2 - o1);
    }

    public void addNum(int num) {
      smallHeap.offer(num);
      bigHeap.offer(smallHeap.poll());
      while (bigHeap.size() > smallHeap.size()) {
        smallHeap.offer(bigHeap.poll());
      }
    }

    public double findMedian() {
      if (smallHeap.size() == bigHeap.size()) {
        return (smallHeap.peek() + bigHeap.peek()) / 2.0d;
      }
      return smallHeap.peek();
    }
  }

  public int getNumberOfBacklogOrders(int[][] orders) {
    PriorityQueue<int[]> buyQ = new PriorityQueue<>((o1, o2) -> o2[0] - o1[0]); // 大 小
    PriorityQueue<int[]> sellQ = new PriorityQueue<>((o1, o2) -> o1[0] - o2[0]); // 小 大
    for (int[] order : orders) {
      int price = order[0], amount = order[1], orderType = order[2];
      if (orderType == 0) {
        // buyQ
        while (amount > 0 && !sellQ.isEmpty() && sellQ.peek()[0] <= price) {
          if (amount >= sellQ.peek()[1]) {
            amount -= sellQ.poll()[1];
          } else {
            int[] poll = sellQ.poll();
            sellQ.offer(new int[] { poll[0], poll[1] - amount });
            amount = 0;
          }
        }
        if (amount > 0) buyQ.offer(new int[] { price, amount });
      } else {
        // sellQ
        while (amount > 0 && !buyQ.isEmpty() && buyQ.peek()[0] >= price) {
          if (amount >= buyQ.peek()[1]) {
            amount -= buyQ.poll()[1];
          } else {
            int[] poll = buyQ.poll();
            buyQ.offer(new int[] { poll[0], poll[1] - amount });
            amount = 0;
          }
        }
        if (amount > 0) sellQ.offer(new int[] { price, amount });
      }
    }
    int result = 0;
    while (!buyQ.isEmpty()) {
      result = (result + buyQ.poll()[1]) % 1000000007;
    }
    while (!buyQ.isEmpty()) {
      result = (result + sellQ.poll()[1]) % 1000000007;
    }
    return result;
  }

  public int nthUglyNumber(int n) {
    int[] ints = { 2, 3, 5 };
    HashSet<Long> set = new HashSet<>();
    PriorityQueue<Long> priorityQueue = new PriorityQueue<>();
    priorityQueue.offer(1l);
    set.add(1l);
    int result = 0;
    for (int i = 0; i < n; i++) {
      long curr = priorityQueue.poll();
      result = (int) curr;
      for (int anInt : ints) {
        long next = curr * anInt;
        if (set.add(next)) priorityQueue.offer(next);
      }
    }
    return result;
  }

  public int maximumScore(int a, int b, int c) {
    PriorityQueue<Integer> priorityQueue = new PriorityQueue<>(
      (o1, o2) -> o2 - o1
    );
    priorityQueue.offer(a);
    priorityQueue.offer(b);
    priorityQueue.offer(c);
    int score = 0;
    while (true) {
      Integer first = priorityQueue.poll();
      Integer second = priorityQueue.poll();
      if (second == 0) break;
      score += 1;
      priorityQueue.offer(first - 1);
      priorityQueue.offer(second - 1);
    }
    return score;
  }
}
