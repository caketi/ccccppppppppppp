import java.util.ArrayList;
import java.util.List;

public class MeregeSort {
  class RangeSum{
    long[] temp;
    public int countRangeSum(int[] nums, int lower, int upper){
        long[] sum = new long[nums.length + 1];
        temp =  new long[sum.length];
        for(int i =0;i < nums.length;i++){
            sum[i+1] = sum[i] + nums[i];
        }
        return countRangeSum(sum, lower, upper, 0, sum.length-1);
    }
    public int countRangeSum(long[] sum, int lower, int upper, int l, int r){
        if(l>=r) return 0;
        int mid = (l+r) >> 1;
        int ans = 0;
         ans+= countRangeSum(sum, lower, upper, l, mid);
         ans+=countRangeSum(sum, lower, upper, mid+1, r);
         int k = l, i = mid+1, j = mid+1;
         while(k <= mid){
            while(i <= r&& sum[i] - sum[k] < lower){
                i++;
            }
            while(j <= r&& sum[j] - sum[k] <= upper){
                j++;
            }
            ans += j -1;
            k++;
         }
         k = l;
         i = l;
         j = mid+1;
         while(i <= mid || j <= r){
            if(j > r || i <= mid && sum[i] <sum[j]){
                temp[k++] = sum[i++];
            }else{
                temp[k++] = sum[j++];
            }
         }
         for(int m = l; m <= r; m++){
            sum[m] = temp[m];
         }
         return ans;
    }
  }
  public class TreeNode{
    int val;
    TreeNode left;
    TreeNode right; 
  }
  class getAllElementsFromBSTToSort{
    public List<Integer> getAllElements(TreeNode root1, TreeNode root2){
        List<Integer> list1 = new ArrayList<>();
        getAllElements(root1, list1);
        List<Integer> list2 = new ArrayList<>();
        getAllElements(root2, list2);
        List<Integer> ans = new ArrayList<>();
        int i = 0;
        int j = 0; 
        while(i < list1.size() || j < list2.size()){
            if(j >= list2.size()|| i < list1.size() && list1.get(i) < list2.get(j)){
                ans.add(list1.get(i++));
            }else {
                ans.add(list2.get(j++));
            }
        }
        return ans;
    }
    public void getAllElements(TreeNode root, List<Integer> list){
        if(root == null) return;
        getAllElements(root.left, list);
        list.add(root.val);
        getAllElements(root.right, list);
    }
  }
  public class ListNode {

    int val;
    ListNode next;

    ListNode() {}

    ListNode(int val) {
      this.val = val;
    }

    ListNode(int val, ListNode next) {
      this.val = val;
      this.next = next;
    }
  }
  class sortLists{
    public ListNode sortList(ListNode head){
        int n = 0;
        ListNode p = head;
        while(p != null){
            p = p.next;
            n++;
        }
        return sortList(head, n);
    }
    public ListNode sortList(ListNode head, int n){
        int l_cnt = n >> 1;
        int r_cnt = n - l_cnt;
        ListNode l = head, r = l, p =l;
        for(int i = 1; i < l_cnt; i++){
            p = p.next;
        } 
        r = p.next;
        p.next = null;
        ListNode ans =new ListNode(0);
        p = ans;
        l = sortList(l, l_cnt);
        r = sortList(r, r_cnt);
        while(l != null || r != null){
            if(r == null || r!=null && l.val < r.val){
                p.next = l;
                l = l.next;
            }else{
                p.next = r;
                r = r.next;
            }
            p = p.next;
        }
        return ans.next;
    }
  }
  class mergeLists {

    public ListNode mergeKLists(ListNode[] lists) {
      return merge(lists, 0, lists.length - 1);
    }

    public ListNode merge(ListNode[] lists, int l, int r) {
      if (l == r) return lists[l];
      if (l > r) return null;
      int mid = (l + r) >> 1;
      return mergeTwoList(merge(lists, l, mid), merge(lists,mid + 1, r));
    }

    public ListNode mergeTwoList(ListNode a, ListNode b) {
      if (a == null || b == null) return a == null ? b : a;
      ListNode head = new ListNode(0);
      ListNode i = a, j = b, tail = head;
      while (i != null || j != null) {
        if (j == null || i != null && i.val < j.val) {
          tail.next = i;
          i = i.next;
        } else {
          tail.next = j;
          j = j.next;
        }
        tail = tail.next;
      }
      return head.next;
    }
  }

  //数组逆序对
  class reversePairsArray {

    int[] temp;

    public int reversePairs(int[] nums, int l, int r) {
      if (l >= r) return 0;
      int mid = (l + r) >> 1;
      int ans = 0;
      ans += reversePairs(nums, l, mid);
      ans += reversePairs(nums, mid + 1, r);

      int i = l, j = mid + 1;
      int k = l;
      while (i <= mid || j <= r) {
        if (j > r || i <= mid && nums[i] <= nums[j]) {
          temp[k++] = nums[i++];
        } else {
          ans += mid - i + 1;
          temp[k++] = nums[j++];
        }
      }
      for (int m = l; m <= r; m++) {
        nums[m] = temp[m];
      }
      return ans;
    }

    public int reversePairs(int[] nums) {
      temp = new int[nums.length];
      return reversePairs(nums, 0, nums.length - 1);
    }
  }

  public int[] mergeSort(int[] array) {
    if (array == null) {
      return array;
    }
    int[] helper = new int[array.length];
    mergeSort(array, helper, 0, array.length - 1);
    return array;
  }

  private void mergeSort(int[] array, int[] helper, int left, int right) {
    if (left >= right) {
      return;
    }
    int mid = left + (right - left) / 2;
    mergeSort(array, helper, left, mid);
    mergeSort(array, helper, mid + 1, right);
    merge(array, helper, left, mid, right);
  }

  private void merge(int[] array, int[] helper, int left, int mid, int right) {
    for (int i = left; i <= right; i++) {
      helper[i] = array[i];
    }
    int leftIndex = left;
    int rightIndex = mid + 1;
    while (leftIndex <= mid && rightIndex <= right) {
      if (helper[leftIndex] <= helper[rightIndex]) {
        array[left++] = helper[leftIndex++];
      } else {
        array[left++] = helper[rightIndex++];
      }
    }

    while (leftIndex <= mid) {
      array[left++] = helper[leftIndex++];
    }
  }
}
