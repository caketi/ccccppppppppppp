import java.security.GeneralSecurityException;
import java.util.Comparator;
import java.util.Deque;

import java.util.LinkedList;
import java.util.List;
import java.util.PriorityQueue;
import java.util.Queue;
class TreeNode{
    int val;
    TreeNode left;
    TreeNode right;
    TreeNode(){}
    TreeNode(int val){this.val =val;}
    TreeNode(int val, TreeNode left, TreeNode right){
        this.val =val;
        this.left =left;
        this.right =right;
    }
}

class lowestCommonAncestorV{
    // 找一个最大和的连续子数组
    public int maxSubArray(int[] nums){
        int sum = 0;
        int ans = nums[0];
        int min = 0;
        for(int i = 0; i < nums.length; i++){
            sum += nums[i];
            ans = Math.max(ans, sum- min);
            min = Math.min(min, sum);
        }
        return ans;
    }
    public int rangeSum(int[] nums, int n, int left, int right){
        Queue<int[]> queue = new PriorityQueue<>(new Comparator<int[]>() {
            public int compare(int[] o1, int[] o2){
                return o1[0]-o2[0];
            }  
        });
        for(int i = 0; i < nums.length; i++){
            queue.offer(new int[]{nums[i], i});
        }
        int sum = 0;
        int curIndex = 1;
        int MOD = 1000000007;
        while(curIndex <= right){
            int[] temp = queue.poll();
            if(curIndex >= left){
                sum = (sum+temp[0] % MOD) % MOD;
            }
            int cur_sum = temp[0];
            int curInd = temp[1];
            if(curIndex + 1 < nums.length){
                queue.offer(new int[]{cur_sum + nums[curInd +1], curInd + 1});
            }
            curIndex++;
        }
        return sum;
    }
    public TreeNode lowestCommonAncestor(TreeNode root, TreeNode p ,TreeNode q){
        if(root == null) return null;
        if(root==p || root == q) return root;
        TreeNode l = lowestCommonAncestor(root.left, p, q);
        TreeNode r = lowestCommonAncestor(root.right, p, q);
        if(l!=null && r==null) return l;
        if(l!=null&&r!=null)return root;
        return r;
    }

}

class deepestLeavesSm{
    int sum = 0;
    int max_k = 0;
    public void getAns(TreeNode root, int k){
        if(root== null) return;
        if(k == max_k) sum += root.val;
        if(k>max_k){
            sum = root.val;
            max_k = k;
        }
        getAns(root.left, k+1);
        getAns(root.right, k+1);
    }
    public  int deepestLeavesSum(TreeNode root){
        getAns(root, 0);
        return sum;
    }
}
// 快速排序思想发散
public class quickSort {

    // 0 1 2 红 白 蓝
    public void sortColors(int[] nums){
        int len = nums.length;
        if(len < 2) return;
        int zero = 0;
        int two = len-1;
        int i = 0;
        while(i < two){
            if(nums[i] == 0){
                swap(nums, zero, i);
                zero++;
                i++;
            }else if(nums[i] == 2){
                swap(nums, i ,two);
                two--;
            }else{
                i++;
            }
        }
    }
    public void swap(int[] nums, int zero, int i){
        int t = nums[i];
        nums[i] = nums[zero];
        nums[zero] = t;
    }
    public List<TreeNode> generateTrees(int n){
        return generateTrees(1, n);
    }
    public List<TreeNode> generateTrees(int l , int r){
        List<TreeNode> list =  new LinkedList<>();
        if(l > r){
            list.add(null);
            return list;
        }
        for(int i = l; i <= r; i++){
            List<TreeNode> leftList = generateTrees(l, i-1);
            List<TreeNode> rightList = generateTrees(i+1, r);
            for(TreeNode leftNode : leftList){
                for(TreeNode rightNode : rightList){
                    list.add(new TreeNode(i, leftNode, rightNode));
                }
            }
        }
        return list;
    }
    public String decodeString(String s){
        Deque<Integer> numStack = new LinkedList<>();
        Deque<StringBuffer> strStack = new LinkedList<>();
        StringBuffer ans = new StringBuffer();
        int num = 0;
        for(char c : s.toCharArray()){
            if(Character.isDigit(c)) num = num * 10 + c -'0';
            else if(Character.isAlphabetic(c)) ans.append(c);
            else if(c == '['){
                numStack.push(num);
                strStack.push(ans);
                num = 0;
                ans = new StringBuffer();
            }else {
                int numTemp = numStack.pop();
                StringBuffer strTemp = strStack.pop();
                for(int i = 0; i < numTemp; i++){
                    strTemp.append(ans);
                }
                ans = strTemp;
            }
        }
        return ans.toString();
    }

    public int maxArea(int[] height){
        int l = 0 , r = height.length - 1;
        int s = 0 ;
        while( l <r){
            s = Math.max(s, (r-l) * Math.min(height[l], height[r]));
            if(height[l] < height[r]){
                l++;
            }else {
                r--;
            }
        }
        return s;
    
    }

    public int rand10(){
        while(true){
            int num = (rand7() -1) * 7 + rand7();// r49
            if(num <= 40) return num % 10 + 1; // r40 -> 410
            num = (num-40-1) * 7 + rand7(); //r9-1 *7 + r7 -> r63
            if(num <= 60) return num % 10 + 1; // r60->r10
            num = (num -60-1)*7 + rand7(); // r3-1 * 7 + r7 -> r21
            if(num <= 20) return num % 10 + 1;
        }

    }
    public int rand7(){
       return rand7();
    }
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
