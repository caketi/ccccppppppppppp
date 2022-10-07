public class MyPQ {

  int[] queue;
  int size;

  public MyPQ() {
    queue = new int[11];
    size = 0;
  }

  public boolean offer(int val) {
    queue[++size] = val; //最后一个位置插入元素
    int index = size; // leftnode > root 需要平衡
    while (index > 1 && queue[index] > queue[index / 2]) {
      int temp = queue[index];

      queue[index] = queue[index / 2];
      queue[index / 2] = temp;
      index = index / 2;
    }
    return true;
  }

  public int poll() {
    // 应该是成环，滑动窗口，
    if (size == 0) return -1;
    int result = queue[1]; //记录队首元素
    queue[1] = queue[size--]; //将队尾元素放到队首
    int index = 1;
    while (index * 2 <= size) { //当前节点是否有左节点
      int maxIndex = index * 2; //left node
      if (maxIndex + 1 <= size && queue[maxIndex] < queue[maxIndex + 1]) {
        maxIndex = maxIndex + 1; // right node
      }
      if (queue[index] >= queue[maxIndex]) { //当前值已经大于左右节点，结束调整
        break;
      }
      int temp = queue[index];
      queue[index] = queue[maxIndex];
      queue[maxIndex] = temp;
      index = maxIndex;
    }
    return result;
  }

  public static void main(String[] args) {
    int[] ints = { 3, 2, 1, 5, 5, 6, 4 };
    MyPQ myPQ = new MyPQ();
    for (int i : ints) {
      myPQ.offer(i);
    }
    for (int i = 0; i < ints.length; i++) {
      System.out.println(myPQ.poll());
    }
  }
}
