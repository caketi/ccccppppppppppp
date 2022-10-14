import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.PriorityQueue;

public class unionFind {

  int[] parent;
  int[] rank;
  int setCount;

  public unionFind(int n) {
    this.parent = new int[n];
    this.rank = new int[n];
    for (int i = 0; i < n; i++) {
      parent[i] = i;
    }
    // rank = new int[];
    Arrays.fill(rank, 1);
    setCount = n;
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
      setCount--;
    }
  }

  public int getSetCount() {
    return setCount;
  }

  public boolean connected(int index1, int index2) {
    return find(index1) == find(index2);
  }

  // 947.移除最多的同行同列的其它石头
  public int removeStones(int[][] stones) {
    int stoneNum = stones.length;
    unionFind uf = new unionFind(stoneNum);
    for (int i = 0; i < stoneNum; i++) {
      for (int j = i + 1; j < stoneNum; j++) {
        int x1 = stones[i][0];
        int y1 = stones[i][1];
        int x2 = stones[j][0];
        int y2 = stones[j][1];
        if (x1 == x2 || y1 == y2) {
          uf.unite(i, j);
        }
      }
    }
    return stoneNum - uf.getSetCount();
  }

  //   1202 字典序最小
  public static String smallestStringWithSwaps(
    String s,
    List<List<Integer>> pairs
  ) {
    int len = s.length();
    unionFind uf = new unionFind(len);
    for (List<Integer> pair : pairs) {
      int index1 = pair.get(0);
      int index2 = pair.get(1);
      uf.unite(index1, index2);
    }
    Map<Integer, PriorityQueue<Character>> map = new HashMap<>();
    for (int i = 0; i < len; i++) {
      int root = uf.find(i);
      map
        .computeIfAbsent(root, key -> new PriorityQueue<Character>())
        .offer(s.charAt(i));
    }
    StringBuffer stringBuffer = new StringBuffer();
    for (int i = 0; i < len; i++) {
      int root = uf.find(i);
      stringBuffer.append(map.get(root).poll());
    }
    return stringBuffer.toString();
  }

  public List<List<String>> accountsMerge(List<List<String>> accounts) {
    Map<String, String> emailToName = new HashMap<>();
    Map<String, Integer> emailToIndex = new HashMap<>();
    int emailCount = 0;
    for (List<String> account : accounts) {
      String name = account.get(0);
      for (int i = 1; i < account.size(); i++) {
        String email = account.get(i);
        if (!emailToIndex.containsKey(email)) {
          emailToIndex.put(email, emailCount++);
          emailToName.put(email, name);
        }
      }
    }
    unionFind uf = new unionFind(emailCount);
    for (List<String> account : accounts) {
      String firstEmail = account.get(1);
      int firstIndex = emailToIndex.get(firstEmail);
      for (int i = 2; i < account.size(); i++) {
        String nextEmail = account.get(i);
        int nextIndex = emailToIndex.get(nextEmail);
        uf.unite(nextIndex, firstIndex);
      }
    }
    Map<Integer, List<String>> IndexToEmails = new HashMap<>();
    for (String email : emailToIndex.keySet()) {
      int index = uf.find(emailToIndex.get(email));
      List<String> list = IndexToEmails.getOrDefault(index, new ArrayList<>());
      list.add(email);
      IndexToEmails.put(index, list);
    }
    List<List<String>> merged = new ArrayList<>();
    for (List<String> emails : IndexToEmails.values()) {
      Collections.sort(emails);
      String name = emailToName.get(emails.get(0));
      List<String> list = new ArrayList<>();
      list.add(name);
      list.addAll(emails);
      merged.add(list);
    }
    return merged;
  }
  // [1,2] [1,3] [2,3] ---- [2,3]
  public int[] findRedundantDirectedConnectionV2(int[][] edges){
    int len = edges.length;
    unionFind uf = new unionFind(len);
    for(int[] edge : edges){
      int node1 = edge[0];
      int node2 = edge[1];
      if(uf.connected(node1, node2)){
        return edge;
      }else {
        uf.unite(node1, node2);
      }
    }
    return edges[0];
  }
  public int[] findRedundantDirectedConnection(int[][] edges) {
    int nodeCount = edges.length;
    unionFind uf = new unionFind(nodeCount + 1);
    int[] parent = new int[nodeCount + 1];
    for (int i = 1; i <= nodeCount; i++) {
      parent[i] = i;
    }
    int conflict = -1;
    int cycle = -1;
    for (int i = 0; i < nodeCount; i++) {
      int[] edge = edges[i];
      int node1 = edge[0], node2 = edge[1];
      if (parent[node2] != node2) {
        conflict = i;
      } else {
        parent[node2] = node1;
        if (uf.find(node1) == uf.find(node2)) {
          cycle = i;
        } else {
          uf.unite(node1, node2);
        }
      }
    }
    if (conflict < 0) {
      int[] redudant = new int[] { edges[cycle][0], edges[cycle][1] };
      return redudant;
    } else {
      int[] conflictEdge = new int[] { edges[conflict][0], edges[conflict][1] };
      if (cycle >= 0) {
        int[] redudant = new int[] { parent[conflictEdge[1]], conflictEdge[1] };
        return redudant;
      } else {
        int[] redudant = new int[] { conflictEdge[0], conflictEdge[1] };
        return redudant;
      }
    }
  }

  // 547省份数量
  public int findCircleNum(int[][] isConnected) {
    int len = isConnected.length;
    unionFind uf = new unionFind(len);
    for (int i = 0; i < len; i++) {
      for (int j = i + 1; j < len; j++) {
        if (isConnected[i][j] == 1) {
          uf.unite(i, j);
        }
      }
    }
    return uf.getSetCount();
  }
//  变量--小写字母，
  public boolean equationsPossible(String[] equations) {
    unionFind uf = new unionFind(26);
    for (String equation : equations) {
      if (equation.charAt(1) == '=') {
        uf.unite(equation.charAt(0) - 'a', equation.charAt(3) - 'a');
      }
    }
    for (String equation : equations) {
      if (equation.charAt(1) == '!') {
        if (uf.connected(equation.charAt(0) - 'a', equation.charAt(3) - 'a')) {
          return false;
        }
      }
    }
    return true;
  }
  
  public int makeConnected(int n, int [][] connections){
    if(n-1> connections.length) return -1;
    unionFind uf = new unionFind(n);
    for(int [] connection : connections){
      uf.unite(connection[0], connection[1]);
    }
    return uf.getSetCount() -1;
  }
  public static void main(String[] args) {
    List<List<Integer>> list = new ArrayList<>();
    list.add(new ArrayList<>(Arrays.asList(1, 3)));
    list.add(new ArrayList<>(Arrays.asList(0, 2)));
    String s = "dcab";
    String res = smallestStringWithSwaps(s, list);
    System.out.println(res);
  }
}
