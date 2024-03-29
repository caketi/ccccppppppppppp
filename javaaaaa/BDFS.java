import java.util.*;
import java.util.HashMap;

class NQueens{
  // Method1: validate the queen position in O(n) each time.
  public List<List<Integer>> nqueens(int n){
    // Assumptions: n > 0
    List<List<Integer>> result = new ArrayList<List<Integer>>();
    // cur will be  a list of size n, and cur[i] is the column number 
    // where the queen on row i positioned.
    List<Integer> cur = new ArrayList<Integer>();
    helper(n, cur, result);
    return result;
  }
  private void helper(int n, List<Integer> cur, List<List<Integer>> result){
    // base case: when for all the rows we know where the queen is positioned.
    if(cur.size() == n){
      result.add(new ArrayList<Integer>(cur));
      return;
    }
    for(int i = 0; i < n; i++){
      // check if putting a queen at colum i at current row is valid
      if(valid(cur, i)){
        cur.add(i);
        helper(n, cur, result);
        cur.remove(cur.size() - 1);
      }
    }
  }
  private boolean valid(List<Integer> cur, int column){
    int row = cur.size();
    for(int i = 0; i < row; i++){
      if(cur.get(i) == column || Math.abs(cur.get(i) - column) == row - i ){
        return false;
      }
    }
    return true;
  }
}




class permutationNumber {

  public List<String> restoreIpAddresses(String s) {
    int n = s.length();
    List<String> res = new ArrayList<>();
    if (n > 12 || n < 4) return res;
    Deque<String> path = new ArrayDeque<>();
    dfsIP(s, n, 0, 4, res, path);
    return res;
  }

  private void dfsIP(
    String s,
    int len,
    int begin,
    int residue,
    List<String> res,
    Deque<String> path
  ) {
    if (begin == len) {
      if (residue == 0) {
        res.add(String.join(".", path));
      }
      return;
    }
    for (int i = begin; i < begin + 1; i++) {
      if (i >= len) break;
      if ((residue - 1) * 3 < len - i - 1) continue;
      if (judgeIpSement(s, begin, i + 1)) {
        String cur = s.substring(begin, i + 1);
        path.addLast(cur);
        dfsIP(s, len, i + 1, residue - 1, res, path);
        path.removeLast();
      }
    }
  }
  private boolean judgeIpSement(String s, int left, int right){
    int len = right - left + 1;
    if(len > 1 && s.charAt(left) == '0'){
      return false;
    }
    int res = 0;
    while(left <= right){
      res = res * 10 + s.charAt(left) - '0';
      left++;
    }
    return res >= 0 && res <= 255;
  }

  // 690.员工的重要性
  class Employee {

    public int id;
    public int importance;
    public List<Integer> subordinates;
  }

  Map<Integer, Employee> map = new HashMap<>();

  public int getImportance(List<Employee> employees, int id) {
    int n = employees.size();
    for (int i = 0; i < n; i++) map.put(employees.get(i).id, employees.get(i));
    int ans = 0;
    Queue<Employee> queue = new LinkedList<>();
    queue.offer(map.get(id));
    while (!queue.isEmpty()) {
      Employee master = queue.poll();
      ans += master.importance;
      for (int oid : master.subordinates) {
        queue.offer(map.get(oid));
      }
    }
    return ans;
    // return getVal(id);
  }

  //  public int getVal(int id){
  //   Employee master = map.get(id);
  //   int ans = master.importance;
  //   for(int subordinateId : master.subordinates){
  //     Employee subordinate = map.get(subordinateId);
  //     ans += subordinate.importance;
  //     for(int oid : subordinate.subordinates) ans += getVal(oid);
  //   }
  //   return ans;
  //  }

  static int N = 10;
  static boolean st[] = new boolean[N];
  static int[] path = new int[N];

  private static void dfs2(int u, int n) {
    if (u == n) {
      for (int i = 0; i < n; i++) {
        System.out.print(path[i] + " ");
      }
      System.out.println();
    }
    // 第一层递归：由多个分支，后续的递归：每次递归的时候所用到的数字
    for (int i = 1; i <= n; i++) {
      if (!st[i] == true) {
        path[u] = i;
        st[i] = true;
        dfs2(u + 1, n);
        // 找到底后，吧啊最上面的数字设计false，回溯
        st[i] = false;
      }
    }
  }

  public static void main(String[] args) {
    Scanner sca = new Scanner(System.in);
    int n = sca.nextInt();
    dfs2(0, n);
  }
}

class NQue {

  static int N = 20;
  static boolean[] row = new boolean[N];
  static boolean[] col = new boolean[N];
  static boolean[] dg = new boolean[N];
  static boolean[] udg = new boolean[N];
  static char[][] path = new char[N][N];

  // 枚举每个鸽子 x-行 y-列
  private static void dfs1(int x, int y, int s, int n) {
    if (y == n) {
      // 当前行满了，跳到下一行
      y = 0;
      x++;
    }
    // 如果最后一行 遍历完了
    if (x == n) {
      //并且皇后个数==行的个数
      if (s == n) {
        for (int i = 0; i < n; i++) {
          for (int j = 0; j < n; j++) {
            System.out.print(path[i][j]);
          }
          System.out.println();
        }
        System.out.println();
      }
      return;
    }
    // 放还是不放皇后
    dfs1(x, y + 1, s, n);
    // 对应的行，列，对角线，不能放
    if (
      !row[x] == true &&
      !col[y] == true &&
      !dg[x + y] == true &&
      !udg[n - x + y] == true
    ) {
      path[x][y] = 'Q';
      row[x] = col[y] = dg[y + x] = udg[n - x + y] = true;
      dfs1(x, y + 1, s + 1, n);
      //回溯，新的答案
      path[x][y] = '.';
      row[x] = col[y] = dg[y + x] = udg[n - x + y] = false;
    }
  }

  // 一个非负整数数组arr，从start位置开始，位于下标i可跳到i+arr[i] // i-arr[i]
  public boolean canReachV2(int[] arr, int start) {
    Queue<Integer> queue = new LinkedList<>();
    int n = arr.length;
    boolean[] visited = new boolean[n];
    queue.add(start);
    while (!queue.isEmpty()) {
      int size = queue.size();
      for (int i = 0; i < size; i++) {
        int curPos = queue.poll();
        int curValue = arr[curPos];
        if (curValue == 0) return true;
        int leftPos = curPos - curValue;
        if (leftPos >= 0 && !visited[leftPos]) {
          visited[leftPos] = true;
          queue.add(leftPos);
        }
        int rightPos = curPos + curValue;
        if (rightPos < n && !visited[rightPos]) {
          visited[rightPos] = true;
          queue.add(rightPos);
        }
      }
    }
    return false;
  }

  public boolean canReach(int[] arr, int start) {
    boolean[] visited = new boolean[arr.length];
    return dfsReach(arr, visited, start);
  }

  public boolean dfsReach(int[] arr, boolean[] visited, int index) {
    if (index < 0 || index > arr.length || visited[index]) return false;
    if (arr[index] == 0) return true;
    visited[index] = true;
    return (
      dfsReach(arr, visited, index + arr[index]) ||
      dfsReach(arr, visited, index - arr[index])
    );
  }

  public static void main(String[] args) {
    Scanner sca = new Scanner(System.in);
    int n = sca.nextInt();
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        path[i][j] = '.';
      }
    }
    dfs1(0, 0, 0, n);
  }
}

class Node1 {

  int x;
  int y;

  public Node1(int x, int y) {
    this.x = x;
    this.y = y;
  }
}

class test {

  // 2 3 4 1 5 x 7 6 8  input
  // 19 output
  // 3 x 3网格，1-8这8个数字和一个x恰好不重不漏分布，x可与其上下左右任意一个数字交换，最终结果要是的网格
  // 1 2 3 4 5 6 7 8 x
  public static void swap(char[] arr, int x, int y) {
    char tmp = arr[x];
    arr[x] = arr[y];
    arr[y] = tmp;
  }

  public static int bfs2(String start) {
    String end = "12345678x"; //最终结果
    Queue<String> qu = new LinkedList<>();
    Map<String, Integer> map = new HashMap();
    qu.offer(start);
    map.put(start, 0);
    while (!qu.isEmpty()) {
      String oldStr = qu.poll();
      if (oldStr.equals(end)) {
        return map.get(oldStr);
      }
      int idx = oldStr.indexOf('x');
      int x = idx / 3;
      int y = idx % 3;
      int[] ds = { 1, 0, -1, 0 };
      int[] dy = { 0, 1, 0, -1 };
      for (int i = 0; i < 4; i++) {
        int newx = x + ds[i];
        int newy = y + dy[i];
        if (newx >= 0 && newy >= 0 && newx < 3 && newy < 3) {
          char[] arr = oldStr.toCharArray();
          swap(arr, idx, newx * 3 + newy);
          String str = new String(arr);
          if (map.get(str) == null) {
            map.put(str, map.get(oldStr) + 1);
            qu.offer(str);
          }
          // 不用回溯，旧状态无用
        }
      }
    }
    return -1;
  }

  public static void main(String[] args) {
    Scanner sca = new Scanner(System.in);
    String start = "";
    for (int i = 0; i < 9; i++) {
      start += sca.next();
    }
    int minTrace = bfs2(start);
    System.out.println(minTrace);
  }
}

class Bfs {

  static Scanner sca = new Scanner(System.in);
  static int n = sca.nextInt();
  static int m = sca.nextInt();
  static int[][] map = new int[n][m];
  static int[][] trace = new int[n][m];

  public static int bfs() {
    Queue<Node1> qu = new LinkedList<>();
    qu.offer(new Node1(0, 0));

    while (!qu.isEmpty()) {
      Node1 oldNode = qu.poll();
      //   位置已经是最后一个了
      if (oldNode.x == n - 1 && oldNode.y == m - 1) break;
      //  查找该位置的上右下左四个
      int[] ds = { 1, 0, -1, 0 };
      int[] dy = { 0, 1, 0, -1 };
      for (int i = 0; i < 4; i++) {
        int newx = oldNode.x + ds[i];
        int newy = oldNode.y + dy[i];
        if (
          newx >= 0 &&
          newy >= 0 &&
          newx < n &&
          newy < m &&
          map[newx][newy] == 0 &&
          trace[newx][newy] == 0
        ) {
          trace[newx][newy] = trace[oldNode.x][oldNode.y] + 1; //新位置的步数=旧位置的步数+1
          qu.offer(new Node1(newx, newy));
        }
      }
    }
    return trace[n - 1][m - 1];
  }

  public static void main(String[] args) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        map[i][j] = sca.nextInt();
      }
    }
    int minTrace = bfs();
    System.out.println(minTrace);
  }
}

// 5 5
// 0 1 0 0 0
// 0 1 0 1 0
// 0 0 0 0 0
// 0 1 1 1 0
// 0 0 0 1 0

class BDFS {

  class Node {

    public Node root;
    public Node left;
    public Node right;
    public int val;
  }

  public void BFS1(Node root) {
    if (root == null) {
      return;
    }
    Queue<Node> q = new LinkedList<Node>();
    q.offer(root);
    while (!q.isEmpty()) {
      int size = q.size();
      for (int i = 0; i < size; i++) {
        Node n = q.remove();
        if (n.left != null) {
          q.offer(n.left);
        }
        if (n.right != null) {
          q.offer(n.right);
        }
        System.out.println(n.val + " ");
      }
      System.out.println();
    }
  }
}
