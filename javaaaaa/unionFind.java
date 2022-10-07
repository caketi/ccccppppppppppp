import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.LinkedList;
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
  public static String smallestStringWithSwaps(String s, List<List<Integer>> pairs){
     int len = s.length();
    unionFind uf = new unionFind(len);
    for(List<Integer> pair : pairs){
        int index1 = pair.get(0);
        int index2 = pair.get(1);
        uf.unite(index1, index2);
    }
    Map<Integer, PriorityQueue<Character>> map = new HashMap<>();
    for(int i = 0; i < len; i++){
        int root = uf.find(i);
        map.computeIfAbsent(root, key -> new PriorityQueue<Character>()).offer(s.charAt(i));
    }
    StringBuffer stringBuffer = new StringBuffer();
    for(int i = 0; i < len; i++){
        int root = uf.find(i);
        stringBuffer.append(map.get(root).poll());
    }
    return stringBuffer.toString();
  }
  public static void main(String[] args){
     
     List<List<Integer>> list = new ArrayList<>();
     list.add(new ArrayList<>(Arrays.asList(1, 3)));
     list.add(new ArrayList<>(Arrays.asList(0, 2)));
     String s = "dcab";
     String res = smallestStringWithSwaps(s, list);
    System.out.println(res);  
  }
}
