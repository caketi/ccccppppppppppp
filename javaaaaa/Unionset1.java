import java.util.HashMap;
import java.util.List;
import java.util.Scanner;
import java.util.Stack;

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
