import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Scanner;
import java.util.Stack;
// 
class sol{
  public int longestConsecutive(int[] nums){
    if(nums.length == 0) return 0;
    unionFindII uf2 = new unionFindII(nums);
    for(int num : nums){
      uf2.union(num, num+1);
    }
    int max  = 0;
    for(int num : nums){
      max =Math.max(max, uf2.find(num)-num+1);
    }
    return max;
  }
}

class unionFindII{
  Map<Integer, Integer> parent;
  int count;
  public unionFindII(int[] arr){
    parent = new HashMap<>();
    for(int i : arr){
      parent.put(i, i);
    }
    count = parent.size();
  }
  public int find(int index){
    int root = index;
    if(parent.get(root) != root){
      root = find(parent.get(root));
    }
    while(index != parent.get(index)){
      int cur =index;
      index = parent.get(index);
      parent.put(cur, root);
    }
    return index;
  }
  public void union(int index1, int index2){
    Integer root1=find(index1), root2= find(index2);
    if(!root1.equals(root2) && root1 != null && root2 != null){
      parent.put(root1, root2);
      count--;
    }
  }
}

class unionFind {

  int[] parent;
  int[] rank;
  int num;
  int setCount;

  public unionFind(int n, int count) {
    this.parent = new int[n];
    this.rank = new int[n];
    for (int i = 0; i < n; i++) {
      parent[i] = i;
    }
    // rank = new int[];
    Arrays.fill(rank, 1);
    setCount = n;
    num = count;
  }

  public int find(int index) {
    if (parent[index] != index) {
      parent[index] = find(parent[index]);
    }
    return parent[index];
  }

  public void unite(int index1, int index2) {
    int root1 = find(index1), root2 = find(index2);
    if (root1 != root2) {
      if (rank[root1] < rank[root2]) {
        int temp = root1;
        root1 = root2;
        root2 = temp;
      }
      parent[root2] = root1; //root1是大哥
      rank[root1] += rank[root2];
      num--;
      setCount--;
    }
  }

  public int getSetCount() {
    return setCount;
  }

  public boolean connected(int index1, int index2) {
    return find(index1) == find(index2);
  }
}
class numIsland{
// 统计数组中元素为‘1’的数量，先把每一个‘1’都看作一块岛屿，并记录数量
// 根据数组的元素个叔叔创建一个并查集
// 遍历整个数组，当当前元素为‘1’，判断当前陆地的下方和有房是否为陆地
// 如果为陆地，将当前坐标与发现的陆地的坐标相连，同时统计出的岛屿的数量-1
// 不需要判断当前岛屿的上方和左方，从第一个元素开始 自左到右，自上而下进行判断

    // 200 岛屿数量
    public int numIslands(char[][] grid) {
      int m = grid.length;
      int n = grid[0].length;
      int count = 0;
      for (char[] chars : grid) {
        for (char aChar : chars) {
          if (aChar == '1') count++;
        }
      }
      unionFind uf = new unionFind(m*n, count);
      for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
          if(grid[i][j] == '1'){
            if(i+1 <m && grid[i+1][j] == '1'){
              uf.unite(i*n+j, (i+1)*n+j);
            }
            if(j+1 < n && grid[i][j+1] == '1'){
              uf.unite(i*n+j, i*n+j+1);
            }
          }
        }
      }
      return uf.num;
    }
}

public class Unionset1 {

  public static class Node<V> {

    V value;

    public Node(V v) {
      value = v;
    }
  }

  public static class Unionset<V> {

    public HashMap<V, Node<V>> nodes;
    public HashMap<Node<V>, Node<V>> parents;
    public HashMap<Node<V>, Integer> sizeMap;

    public Unionset(List<V> values) {
      nodes = new HashMap<>();
      parents = new HashMap<>();
      sizeMap = new HashMap<>();
      for (V cur : values) {
        Node<V> node = new Node<>(cur);
        nodes.put(cur, node);
        parents.put(node, node);
        sizeMap.put(node, 1);
      }
    }

    public Node<V> findFather(Node<V> cur) {
      Stack<Node<V>> path = new Stack<>();
      while (cur != parents.get(cur)) {
        path.push(cur);
        cur = parents.get(cur);
      } ////  cur == parents.get(cur)
      while (!path.isEmpty()) {
        parents.put(path.pop(), cur);
      }
      return cur;
    }

    public boolean isSameSet(V a, V b) {
      return findFather(nodes.get(a)) == findFather(nodes.get(b));
    }

    public void union(V a, V b) {
      Node<V> aHead = findFather(nodes.get(a));
      Node<V> bHead = findFather(nodes.get(b));
      if (aHead != bHead) {
        int aSetSize = sizeMap.get(aHead);
        int bSetSize = sizeMap.get(bHead);
        Node<V> big = aSetSize >= bSetSize ? aHead : bHead;
        Node<V> small = big == aHead ? bHead : aHead;
        parents.put(small, big);
        sizeMap.put(big, aSetSize + bSetSize);
        sizeMap.remove(small);
      }
    }
  }
}

// 4 5
// M 1 2
// M 3 4
// Q 1 2
// Q 1 3
// Q 3 4
class Unionset2 {

  static int N = 100010;
  static int[] p = new int[N];

  public static int find(int x) {
    if (p[x] != x) {
      p[x] = find(p[x]);
    }
    return p[x];
  }

  public static void main(String[] args) {
    Scanner sca = new Scanner(System.in);
    String[] str = sca.nextLine().split(" ");
    int n = Integer.parseInt(str[0]);
    int m = Integer.parseInt(str[1]);
    for (int i = 1; i <= n; i++) p[i] = i;
    while (m-- > 0) {
      String op = sca.next();
      int a = sca.nextInt();
      int b = sca.nextInt();
      if (op.equals("M")) {
        p[find(a)] = find(b);
      } else {
        if (find(a) == find(b)) {
          System.out.println("YES");
        } else {
          System.out.println("NO");
        }
      }
    }
  }
}
// 5 5
// C 1 2
// Q1 1 2
// Q2 1 
// C 2 5
// Q2 5
// Q2--查询集合中 有多少个点
class a {

  static int N = 100010;
  static int[] p = new int[N];
  static int[] size = new int[N];

  public static int find(int x) {
    if (p[x] != x) {
      p[x] = find(p[x]);
    }
    return p[x];
  }

  public static void main(String[] args) {
    Scanner sca = new Scanner(System.in);
    int n = sca.nextInt();
    int m = sca.nextInt();
    for (int i = 1; i <= n; i++) {
      p[i] = i;
      size[i] = 1;
    }
    while (m-- > 0) {
      String op = sca.next();
      if (op.equals("C")) {
        int a = sca.nextInt();
        int b = sca.nextInt();
        if (find(a) != find(b)) size[find(b)] += size[find(a)];
        p[find(a)] = find(b);
      } else if (op.equals("Q1")) {
        int a = sca.nextInt();
        int b = sca.nextInt();
        if (find(a) == find(b)) {
          System.out.println("YES");
        } else {
          System.out.println("NO");
        }
      } else {
        int a = sca.nextInt();
        System.out.println(size[find(a)]);
      }
    }
  }
}
