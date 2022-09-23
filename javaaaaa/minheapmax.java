import java.util.Collections;
import java.util.PriorityQueue;

// left child index: i = 2*i +1
// right child index: i = 2*i + 2
// parent child index: i = (i-1)/2
// heapify()
// percolateUp()
// percolateDown()
public class minheapmax {
    private int[] array;
    private int size;
    public minheapmax(int[] array){
        if(array == null || array.length == 0){
            throw new IllegalArgumentException("input array can not be null or empty");
        }
        this.array =array;
    }
    
    public static void main(String[] args){
        int[] arr = {3,4,1,2,5};
        int[] resMinHeap = kSmallest(arr, 3);
        int[] resMaxHeap = kSmallestMaxHeap(arr, 3);
        System.out.println("=====Original arr======");
        for(int i : arr){
            System.out.print(i);
        }
        System.out.println();
        System.out.println("=====3-SmallestMinHeap======");
        for(int i : resMinHeap){
            System.out.print(i);
        }
        System.out.println();
        System.out.println("=====3-SmallestMaxHeap======");
        for(int i : resMaxHeap){
            System.out.print(i);
        }
    }

    // public int size(){
    //     return size;
    // }
    // public boolean isEmpty(){
    //     return size == 0;
    // }
    // public boolean isFull(){
    //     return size == array.length;
    // }
    // public int poll(){return 0;}
    // public void offer(int ele){}
    // public int peek(){return array[0];}
    // private void percolateUp(int index){}
    // private void percolateDown(int index){
    //     while(index <= (size-2)/2){
    //         int leftChildIndex = index * 2 + 1;
    //         int rightChildIndex = index * 2 + 2;
    //         int swapCandidate = leftChildIndex; // samllest one among leftchild and rightchild
    //         // update swapCandidate if rightchild exists and smaller than leftChild
    //          if(rightChildIndex <= size-1 && array[leftChildIndex]>=array[rightChildIndex]){
    //             swapCandidate = rightChildIndex;
    //          }
    //          if(array[index] > array[swapCandidate]){
    //             swap(array, index, swapCandidate);
    //          }else {
    //             break;
    //          }
    //          index = swapCandidate;
    
    //     }
    // }
    //  a = {3,4,1,2,5} k = 3 {1,2,3}
    // maxheap====== online === realtime?
    public static int[] kSmallestMaxHeap(int[] array, int k){
        if(array.length == 0 || k == 0){
            return new int[0];
        }
        PriorityQueue<Integer> maxHeap = new PriorityQueue<>(k, Collections.reverseOrder());
        for(int i = 0; i < array.length; i++){
            if(i < k){
                maxHeap.offer(array[i]); // 我先假设维持最小的k个数
            } else if(array[i] < maxHeap.peek()){ // 和最大值比较，你小它走
                maxHeap.poll(); 
                maxHeap.offer(array[i]);
            }
        }
        int[] result = new int[k];
        for(int i = k-1; i>=0; i--){
            result[i] = maxHeap.poll();
        }
        return result;
    }



    // minheap ---- offline ---all data in 
    public static int[] kSmallest(int[] array, int k){
        if(array.length == 0 || k == 0){
            return new int[0];
        }
        PriorityQueue<Integer> minHeap = new PriorityQueue<>();
        for(int i = 0; i<array.length;i++){
            minHeap.offer(array[i]); //全部入堆
        }
        int[] result =new int[k];
        for(int j = 0; j<k; j++){
            result[j] = minHeap.poll(); //出兑
        }
        return result;
    }
}
