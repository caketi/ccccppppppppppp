import java.util.HashMap;
import java.util.TreeMap;

public class hashta {
    public static class Node{
        int value;
        Node(int n){
            value = n;
        }
    }
    public static void main(String[] args){
        HashMap<String, String> m = new HashMap<>();
        m.put("test", "this is test!!!");
        System.out.println(m.get("test"));

        // 原生 type by value
        HashMap<Integer, String> m2 = new HashMap<>();
        m2.put(1,"ffff");
        Integer a = 1;
        Integer b = 1;
        System.out.println(m2.containsKey(b));
        System.out.println(m2.containsKey(a));
        // by reference 
        Node node1 = new Node(1);
        Node node2 = new Node(2);
        HashMap<Node,String> m3 = new HashMap<>();
        m3.put(node1,"ffff");
        System.out.println(m3.containsKey(node1));
        System.out.println(m3.containsKey(node2));

        TreeMap<Integer, String> tm = new TreeMap<>();
        tm.put(1, "11");
        tm.put(0,"fff");
        tm.put(111,"fffff");
        System.out.println(tm.firstKey());
        System.out.println(tm.lastKey());
        System.out.println(tm.floorKey(2)); // <= 2
        System.out.println(tm.ceilingKey(10)); // >= 10
    }
}
