import java.util.*;
import java.util.HashMap;


class BitSet{
    int size, base, n, cnt;
    int[] data;
    public void  Bitset(int size){
        this.size = size;
        base = 30;
        cnt = 0;
        n = size / base + (size % base == 0 ? 0 :  1);
        data = new int[n];
    }
    // 下标idx的值更新为1
    public void fix(int idx){
        int x = idx / base, y = idx % base;
        if((data[x] & (1 << y)) == 0){
            cnt++;
            data[x] |= (1 << y);
        }
    }
    // 下标idx的值更新为0
    public void unfix(int idx){
        int x = idx / base, y = idx % base;
        if((data[x] & (1<<y)) != 0){
            cnt--;
            data[x] ^= (1<<y);
        }
    }
    // 翻转
    public void flip(){
        for(int i=0; i < n; i++){
            data[i] = ~data[i];
        }
        cnt = size -cnt;
    }
    // 检查每一位是否为1
    public boolean all(){
        return cnt == size;
    }
    // 至少有一位为1
    public boolean one(){
        return cnt > 0;
    }
    public int count(){
        return cnt;
    }
    public String toString(){
         StringBuffer s = new StringBuffer();
         int x = size / base, y = size % base;
         for(int i = 0; i < x; i++){
            for(int j = 0; j < base; j++){
                if((1<<j& data[i]) != 0) s.append(1);
                else s.append(0);
            }
         }
         for(int i  =0; i < y; i++){
            if((1<<i & data[n-1])!= 0) s.append(1);
            else s.append(0);
         }
         return s.toString();
    }

}

//java int 0-31
public class bitOpr {
    // 2163.删除元素后和的最小差值
    // 元素个数： 3 * n 可以从中删除恰好n个元素，剩下的2*n平分
    // 前面n个 和 sumfrist 后面n个sumsecond。 sumfirst-sumsecond差值的最小值
    // 前面删掉尽可能大的，后面删掉尽可能小的 2个堆，大堆 小堆
    public long minimumDifference(int[] nums){
        int m = nums.length;
        int n = m / 3;
        long ans = Long.MAX_VALUE;
        PriorityQueue<Integer> left = new PriorityQueue<>((o1, o2) -> o2 - o1); 
        PriorityQueue<Integer> right = new PriorityQueue<>();
        long[] lsum = new long[m];
        long sum = 0;
        for(int i  =0; i< m;i++){
            sum += nums[i];
            left.offer(nums[i]);
            if(left.size() < n) continue;
            if(left.size() > n) sum -= left.poll(); //去掉大的
            lsum[i] = sum; 
        }
        sum = 0;
        for(int i = m -1; i >= n;i --){
            sum += nums[i];
            right.offer(nums[i]);
            if(right.size() < n) continue ;
            if(right.size() > n) sum -= right.poll(); //去掉小的
            ans = Math.min(ans, lsum[i-1] - sum); //i是右边开始的部分，i-1左边
        }
        return ans;
    }


    // 2151.基于陈述统计最多好人数量
    // 好人： 只说真话 坏人：真、假 statements[i][j] -- 0 1 2 i认为j是 坏人、好人、没说
    // 玩家不会对自己进行陈述
    public int maximumGood(int[][] statements){
        int n = statements.length, ans = 0;
        for(int i = 0, I = 1 << n; i< I; i++){
            if(!check(statements, i, n)) continue;
            ans = Math.max(ans, Integer.bitCount(i));
        }
        return ans;
    }
    public boolean check(int[][] statements,int mark, int n){
        for(int i = 0; i <  n; i++){
            if(((mark >> i) & 1) == 0) continue;
            for(int j = 0; j < n; j++){
                if(statements[i][j] == 2) continue;
                if(statements[i][j] != ((mark >> j) & 1)){
                    return false;
                }
            }
        }
        return true;
    }



    // 279.n = 12 output=3  
    // 1 + 4 + 9  n叉树 
    public int nuSquares(int n){
        Queue<Integer> queue = new LinkedList<>();
        Set<Integer> set = new HashSet<>();
        queue.offer(0);
        set.add(0);
        int level = 0;
        while(!queue.isEmpty()){
            int size = queue.size();
            level++;
            for(int i = 0; i < size; i++){
                int digit = queue.poll();
                for(int j = 1; j <= n; j++){
                    int nodeVal = j * j + digit;
                    if(nodeVal == n) return level;
                    if(nodeVal > n) break;
                    if(!set.contains(nodeVal)){
                        queue.offer(nodeVal);
                        set.add(nodeVal);
                    }
                }
            }
        }
        return level;

    }
    public int fibV2(int n ){
        HashMap<Integer,Integer> fibMap = new HashMap<>();
        if(n < 2) return n;
        if(fibMap.containsKey(n)) return fibMap.get(n);
        int result = (fibV2(n-1) + fibV2(n-2)) % 1000000007;
        fibMap.put(n, result);
        return result;
    }
    public int fib(int n){
        int a = 0, b = 1, sum;
        for(int i = 0; i < n; i++){
            sum = (a+b) % 1000000007;
            a = b;
            b = sum;
        }
        return a;
    }
    // k奇数（k%2 == 1）----与上一行(k+1)/2相同
    // k偶数 与上一行k/2相反
    public int kthGrammar(int N, int K){
        if (N==0) return 0;
        if(K % 2 == 1) return kthGrammar(N-1, (K+1)/2);
        else return  Math.abs(kthGrammar(N-1, (K/2) -1));
    }
    public static int add(int a, int b){
        int sum = a;
        while(b!=0){
            sum = a^b;
            b = (a&b) << 1;
            a = sum;
        }
        return sum;
    }
    public static int negNum(int n){
        return add(~n, 1);
    }
    public static int minus(int a, int b){
        return add(a, negNum(b));
    }
    public static int multi(int a, int b){
        int res = 0;
        while(b!=0){
            if((b&1) != 0){  //位为1则加a
                res = add(res, a); 
            }
            a <<= 1;
            b >>>= 1;
        }
        return res;
    }


    public static void printBit(int num) {
        for (int i = 31; i >= 0; i--) {
            System.out.print(((num) & (1 << i)) == 0 ? "0" : "1");
        }
        System.out.println();
    }
   
    int[] preSum;
    public  void RangeSum2(int[] arr){
        int N = arr.length;
        preSum = new int[N];
        preSum[0] = arr[0];
        for(int i = 1; i < N; i++){
            preSum[i] = preSum[i-1] + arr[i];
        }
    }
    public int rangeSum(int L, int R){
        return L == 0? preSum[R] : preSum[R] - preSum[L-1];
    }

    public static void swap(int[] arr, int a, int b){
        int tmp = arr[b];
        arr[b] = arr[a];
        arr[a] = tmp;
    }
    public static void selectsort(int[] arr){
        if(arr == null || arr.length < 2) return;
        int N = arr.length;
        for(int i = 0; i< N; i++){
            int minValueIndex = i;
            for(int j =i +1; j<N; j++){
                minValueIndex = arr[j] < arr[minValueIndex] ? j:minValueIndex;
            }
            swap(arr, i ,minValueIndex);
        }
    }
    public static void bubblesort(int[] arr){
        if(arr == null || arr.length < 2) return;
        int N = arr.length;
        for(int end = N-1; end >= 0; end--){
            for(int second = 1; second <= end; second++){
                if(arr[second-1] > arr[second]){
                    swap(arr, second-1, second);
                }
            }
        }
    }
    public static void insertsort1(int[] arr){
        if(arr == null || arr.length < 2) return;
        int N = arr.length;
        for(int end = 1; end < N; end++){
            for(int pre = end -1; pre>=0 && arr[pre] > arr[pre+1]; pre--){
                swap(arr, pre, pre+1);
            }
            // int newNumIndex = end;
            // while(newNumIndex - 1 >= 0 && arr[newNumIndex-1] > arr[newNumIndex]){
            //     swap(arr, newNumIndex-1, newNumIndex);
            //     newNumIndex--;
            // }
        }

    }
    public static void main(String[] args) {
        // int num = -1;
        // double n = 2e31;
        // int min = Integer.MIN_VALUE;
        // int max = Integer.MAX_VALUE;
        // System.out.println(min); //2^31 -1
        // System.out.println(max); // 2^31
        // System.out.println(n);
        // System.out.println("=======signed-shift=========");
        // printBit(min >> 1);
        // System.out.println("=======unsigned-shift=========");
        // printBit(min>>>1);
        // System.out.println("=======最小取反+1=========");
        // int b_min = ~min+1;
        // System.out.println(b_min);
        // printBit(min | max);
        // printBit(min & max);
        // printBit(min ^ max);

        int[] arr = { 3, 4,1,2};
        // bubblesort(arr);
       
        
        insertsort1(arr);
        for(int i : arr){
            System.out.print(i);
        }
        // print(min);
        // print(num);//11111111111111111111111111111111
        // 1 .... 取反+1 -1
    }
}
