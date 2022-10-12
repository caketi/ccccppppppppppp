import java.util.Deque;
import java.util.LinkedList;

public class quickSort {
    // 返回滑动串口中的最大值 [1,3,-1,-3,5,3,6,7], k=3 [3,3,5,5,6,7]
    public int[]  maxSlidingWindows(int[] nums, int k){
        int n  = nums.length;
        Deque<Integer> deque = new LinkedList<>();
        for(int i = 0; i < k; i++){ //定下滑动窗口的大小k
            while(!deque.isEmpty()&& nums[deque.peekLast()] < nums[i]){
                deque.pollLast();
            }
            deque.offer(i);
        }
        int[] ans =new int[n-k+1];
        ans[0] = nums[deque.peekFirst()];
        for(int i = k ; i < nums.length; i++){//开始滑动
            while(!deque.isEmpty() && nums[deque.peekLast()] < nums[i]){
                deque.pollLast();
            }
            deque.offer(i);
            while(deque.peekFirst() <= i-k){
                deque.pollFirst();
            }
            ans[i-k+1] = nums[deque.peekFirst()];
        }
        return ans;
    }
    public static void main(String[] args){
        quickSort msw = new quickSort();
        int[] nums = {1,3,-1,-1,-3,5,3,6,7};
        int[] ans = msw.maxSlidingWindows(nums, 3);
        for(int i : ans){
            System.out.print(i+" ");
        }
    }
}
