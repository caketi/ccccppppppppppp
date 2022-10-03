import java.util.ArrayList;
import java.util.Deque;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Stack;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.stream.Collectors;
import javax.xml.transform.TransformerException;

public class bst {

  public static void print(int x) {
    if (x <= 0) {
      return;
    }
    print(x - 1);
    System.out.println(x);
  }

  public static void main(String[] args) {
    print(10);
  }

  public static class TreeNode {

    public int value;
    public TreeNode root;
    public TreeNode right;
    public TreeNode left;
  }

  public static void postOrder(TreeNode root) {
    if (root == null) {
      return;
    }

    Deque<TreeNode> stack = new LinkedList<>();
    TreeNode prev = null;
    stack.offerFirst(root);

    while (!stack.isEmpty()) {
      TreeNode current = stack.peekFirst();

      if (prev == null || current == prev.left || current == prev.right) {
        if (current.left != null) {
          stack.offerFirst(current.left);
        } else if (current.right != null) {
          stack.offerFirst(current.right);
        } else {
          System.out.println(current.value);
          stack.pollFirst();
        }
      } else if (prev == current.left) {
        if (current.right != null) {
          stack.offerFirst(current.right);
        } else {
          System.out.println(current.value);
          stack.pollFirst();
        }
      } else {
        System.out.println(current.value);
        stack.pollFirst();
      }

      prev = current;
    }
  }

  public static List<Integer> inOrder(TreeNode root) {
    List<Integer> result = new ArrayList<>();
    if (root == null) {
      return result;
    }
    Deque<TreeNode> stack = new LinkedList<>();
    TreeNode next = root;
    while (next != null || !stack.isEmpty()) {
      if (next != null) {
        stack.offerFirst(next);
        next = next.left;
      } else {
        next = stack.pollFirst();
        result.add(next.value);
        next = next.right;
      }
    }
    return result;
  }

  public static void preOrder(TreeNode root) {
    if (root == null) {
      return;
    }
    Deque<TreeNode> stack = new LinkedList<TreeNode>();
    stack.offerFirst(root);
    while (!stack.isEmpty()) {
      TreeNode cur = stack.pollFirst();
      System.out.println(cur.value);
      if (cur.right != null) {
        stack.offerFirst(cur.right);
      }
      if (cur.left != null) {
        stack.offerFirst(cur.left);
      }
    }
  }

  class getMinDiffV2 {

    TreeNode pre;
    Stack<TreeNode> stack;

    public int getMinmumDifference(TreeNode root) {
      if (root == null) return 0;
      stack = new Stack<>();
      TreeNode cur = root;
      int result = Integer.MAX_VALUE;
      while (cur != null || !stack.isEmpty()) {
        if (cur != null) {
          stack.push(cur);
          cur = cur.left;
        } else {
          cur = stack.pop();
          if (pre != null) {
            result = Math.min(result, cur.value - pre.value);
          }
          pre = cur;
          cur = cur.right;
        }
      }
      return result;
    }
  }

  class getMinDiff {

    TreeNode pre;
    int result = Integer.MAX_VALUE;

    public int getMinumDifference(TreeNode root) {
      if (root == null) return 0;
      traversal(root);
      return result;
    }

    public void traversal(TreeNode root) {
      if (root == null) return;
      traversal(root.left);
      if (pre != null) {
        result = Math.min(result, root.value - pre.value);
      }
      pre = root;
      traversal(root.right);
    }
  }

  //   暴力
  class findMostTimesNumberMayBeManyV3 {

    void searchBST(TreeNode curr, Map<Integer, Integer> map) {
      if (curr == null) return;
      map.put(curr.value, map.getOrDefault(curr.value, 0) + 1);
      searchBST(curr.left, map);
      searchBST(curr.right, map);
    }

    public int[] findMode(TreeNode root) {
      Map<Integer, Integer> map = new HashMap<>();
      List<Integer> list = new ArrayList<>();
      if (root == null) return list
        .stream()
        .mapToInt(Integer::intValue)
        .toArray();

      searchBST(root, map);
      List<Map.Entry<Integer, Integer>> mapList = map
        .entrySet()
        .stream()
        .sorted((c1, c2) -> c2.getValue().compareTo(c1.getValue()))
        .collect(Collectors.toList());
      list.add(mapList.get(0).getKey());
      for (int i = 1; i < mapList.size(); i++) {
        if (mapList.get(i).getValue() == mapList.get(i - 1).getValue()) {
          list.add(mapList.get(i).getKey());
        } else {
          break;
        }
      }
      return list.stream().mapToInt(Integer::intValue).toArray();
    }
  }

  //   迭代
  class findMostTimesNumberMayBeManyV2 {

    public int[] findMode(TreeNode root) {
      TreeNode pre = null;
      Stack<TreeNode> stack = new Stack<>();
      List<Integer> result = new ArrayList<>();
      int maxCount = 0;
      int count = 0;
      TreeNode cur = root;
      while (cur != null || !stack.isEmpty()) {
        if (cur != null) {
          stack.push(cur);
          cur = cur.left;
        } else {
          cur = stack.pop();
          if (pre == null || cur.value != pre.value) {
            count = 1;
          } else {
            count++;
          }
          if (count > maxCount) {
            maxCount = count;
            result.clear();
            result.add(cur.value);
          } else if (count == maxCount) {
            result.add(cur.value);
          }
          pre = cur;
          cur = cur.right;
        }
      }
      return result.stream().mapToInt(Integer::intValue).toArray();
    }
  }

  class findMostTimesNumberMayBeMany {

    ArrayList<Integer> resList;
    int maxCount;
    int count; // pre.val == cur.val count++;
    TreeNode pre;

    public void findMode1(TreeNode root) {
      if (root == null) {
        return;
      }
      findMode1(root.left);
      int rootValue = root.value;
      if (pre == null || rootValue != pre.value) {
        count = 1; //当前节点和前一个节点值不等
      } else {
        count++;
      }
      if (count > maxCount) { //更新众数，，最终结果的众数的maxCount
        resList.clear();
        resList.add(rootValue);
        maxCount = count;
      } else if (count == maxCount) {
        resList.add(rootValue);
      }
      pre = root; //回溯更新pre
      findMode1(root.right);
    }

    public int[] findMode(TreeNode root) {
      resList = new ArrayList<>();
      maxCount = 0;
      count = 0;
      pre = null;
      findMode1(root);
      int[] res = new int[resList.size()];
      for (int i = 0; i < resList.size(); i++) {
        res[i] = resList.get(i);
      }
      return res;
    }
  }
  //
  // public void inorder(TreeNode root){
  // if(root== null){
  // return;
  // }
  // inorder(root.left);
  // System.out.println(root.key);
  // inorder(root.right);
  // }
  // private TreeNode deleteSmallest(TreeNode cur){
  // TreeNode prev = cur;
  // cur = cur.left;
  // while(cur.left!=null){
  // prev = cur;
  // cur = cur.left;
  // }
  // prev.left = prev.left.right;
  // return cur;
  // }
  // public TreeNode delete(TreeNode root, int target){
  // if(root==null){
  // return null;
  // }
  // if(root.val > target){
  // root.left = delete(root.left, target);
  // return root;
  // } else if(root.val<target){
  // root.right = delete(root.right, target);
  // return root;
  // }
  // guarantee root != null && root.val == target;
  // if(root.left == null){
  // return root.right;
  // } else if(root.right == null){
  // return root.left;
  // }
  // node.right does not has left child, meaning itself is the samllest node in
  // this case, we just move node.right up
  // if(root.right.left == null){
  // root.right.left = root.left;
  // return root.right;
  // }
  // node.right has left child, we need to find the smallest node, and move it up.
  // TreeNode smallest = deleteSmallest(root.right);
  // smallest.left = root.left;
  // smallest.right = root.right;
  // return smallest;
  // }

  // public static TreeNode insert(TreeNode root, int target){
  // if(root == null){
  // return new TreeNode(target);
  // }
  // helper(root, target);
  // return root;
  // }
  // public static void helper(TreeNode root, int target){
  // if(target == root.key){
  // return;
  // }else if(target < root.key){
  // if(root.left == null){
  // root.left = new TreeNode(target);
  // }else {
  // helper(root.left, target);
  // }
  // } else {
  // if(root.right == null){
  // root.right = new TreeNode(target);
  // } else {
  // helper(root.right, target);
  // }
  // }
  // }

  // public TreeNode insert(TreeNode root, int target){
  // TreeNode newNode = new TreeNode(target);
  // if(root == null){
  // return newNode;
  // }
  // TreeNode current = root;
  // while(current.key != target){
  // if(current.key > target){
  // if(current.left != null){
  // current = current.left;
  // }else{
  // current.left = newNode;
  // break;
  // }
  // } else{
  // if(current.key < target){
  // if(current.right != null){
  // current = current.right;
  // }else {
  // current.right = newNode;
  // break;
  // }
  // }
  // }
  // }
  // return root;
  // }

  // public TreeNode insert(TreeNode root, int key){
  // if(root == null){
  // TreeNode newRoot = new TreeNode(key);
  // return newRoot;
  // }
  // if(root.key<key){
  // root.right = insert(root.right, key);
  // }else if(root.key > key){
  // root.left = insert(root.left, key);
  // }
  // return root;
  // }
  // iterative
  // public TreeNode search(TreeNode root, int target){
  // TreeNode currentNode = root;
  // while(currentNode != null && currentNode.key != target){
  // if(target < currentNode.key){
  // currentNode = currentNode.left;
  // } else {
  // currentNode = currentNode.right;
  // }
  // }
  // // currentNode = null || currentNode.key == target
  // return currentNode;
  // }
  // recursion
  // public TreeNode search(TreeNode root, int target){
  // while(root != null){
  // if(target < root.key){
  // root = root.left;
  // } else if (target > root.key){
  // root =root.right;
  // }else {
  // return root;
  // }

  // }
  // return null;
  // }
  // // tail recursion
  // public TreeNode search(TreeNode root, int target){
  // if(root== null || root.key == target){
  // return root;
  // }
  // if(target<root.key){
  // return search(root.left, target);
  // }else {
  // return search(root.right, target);
  // }
  // }
}
