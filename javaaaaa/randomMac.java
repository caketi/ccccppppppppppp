
public class randomMac {
    // arr有序， >= num 最左
    public static int mostLeftNoLessNumIndex(int[] arr, int num) {
        if (arr == null || arr.length == 0) {
            return -1;
        }
        int ans = -1;
        int L = 0;
        int R = arr.length - 1;
        while (L <= R) {
            int mid = (L + R) / 2;
            if (arr[mid] >= num) {
                ans = mid;
                R = mid - 1;
            } else {
                L = mid + 1;
            }
        }
        return ans;
    }

    // 局部最小
    public static int oneMinIndex(int[] arr) {
        if (arr == null || arr.length == 0)
            return -1;
        int N = arr.length;
        if (N == 1)
            return 0;
        if (arr[0] < arr[1])
            return 0;
        if (arr[N - 1] < arr[N - 2])
            return N - 1;
        int L = 0;
        int R = N - 1;
        // int ans = -1;
        // L..R 局部最小有
        while (L <= R) {
            int mid = (L + R) / 2;
            if (arr[mid] < arr[mid - 1] && arr[mid] < arr[mid + 1]) {
                // ans = mid;
                // break;
                return mid;
            } else {
                // 1. L > mid && mid > R
                // 2. L < mid && mid < R
                // 3. L < mid && mid > R
                if (arr[mid] > arr[mid - 1]) {
                    R = mid - 1;
                } else {
                    L = mid + 1;
                }
            }
        }
        return arr[L] < arr[R] ? L : R;
        // return ans;
    }

    // 生成随机数组，相邻数不相等
    public static int[] randomArray(int maxLen, int maxValue) {
        int len = (int) (Math.random() * maxLen);
        int[] arr = new int[len];
        if (len > 0) {
            arr[0] = (int) (Math.random() * maxValue);
            for (int i = 1; i < len; i++) {
                do {
                    arr[i] = (int) (Math.random() * maxValue);
                } while (arr[i] == arr[i - 1]);
            }
        }
        return arr;
    }

    public static boolean check(int[] arr, int minIndex) {
        if (arr.length == 0) {
            return minIndex == -1;
        }
        int left = minIndex - 1;
        int right = minIndex + 1;
        boolean leftBigger = left >= 0 ? arr[left] > arr[minIndex] : true;
        boolean rightBigger = right < arr.length ? arr[right] > arr[minIndex] : true;
        return leftBigger && rightBigger;
    }

    // 返回[0,1)
    // x出现在此区间的概率有x调整成x平方
    public static double xToXPower2() {
        return Math.min(Math.random(), Math.random());
    }

    public static int f1() {
        return (int) (Math.random() * 5) + 1;
    }

    // 等概率返回0 和 1
    // 随机机制 只能使用f1()
    public static int f2() {
        int ans = 0;
        do {
            ans = f1();
        } while (ans == 3);
        return ans < 3 ? 0 : 1;
    }

    // 000-111 等概率返回0-7
    public static int f3() {
        return (f2() << 2) + (f2() << 1) + f2();
    }

    // 0-6等概率返回
    public static int f4() {
        int ans = 0;
        do {
            ans = f3();
        } while (ans == 7);
        return ans;
    }

    public static int x() {
        return Math.random() < 0.84 ? 0 : 1;
    }

    // 等概率返回0 1
    public static int y() {
        int ans = 0;
        do {
            ans = x();
        } while (ans == x()); // ans = 1 1 or ans = 00 重做
        return ans;// ans = 0 1 or ans = 1 0
    }

    public static int[] lenRandomValueRandom(int maxLen, int maxValue) {
        int len = (int) (Math.random() * maxLen);
        int[] ans = new int[len];
        for (int i = 0; i < len; i++) {
            ans[i] = (int) (Math.random() * maxValue);
        }
        return ans;
    }

    public static int[] copyArray(int[] arr) {
        int[] ans = new int[arr.length];
        for (int i = 0; i < arr.length; i++) {
            ans[i] = arr[i];
        }
        return ans;
    }

    public static boolean isSorted(int[] arr) {
        if (arr.length < 2) {
            return true;
        }
        int max = arr[0];
        for (int i = 1; i < arr.length; i++) {
            if (max > arr[i]) {
                return false;
            }
            max = Math.max(max, arr[i]);
        }
        return true;
    }

    public static void swap(int[] arr, int a, int b) {
        int tmp = arr[b];
        arr[b] = arr[a];
        arr[a] = tmp;
    }
    //插入排序由N-1趟排序组成。对于p=1到N-1趟排序后，插入排序保证从位置0到位置p上的元素为已排序状态。即插入排序利用了从位置0到p-1位置上已经有序的条件，将位置p上的元素向前查找适当的位置插入此元素。
    public static void insertionSort(int[] arr) {
        if (arr == null || arr.length < 2)
            return;
        int N = arr.length;
        for (int end = 1; end < N; end++) {
            for (int pre = end - 1; pre >= 0 && arr[pre] > arr[pre + 1]; pre--) {
                swap(arr, pre, pre + 1);
            }
            // int newNumIndex = end;
            // while(newNumIndex - 1 >= 0 && arr[newNumIndex-1] > arr[newNumIndex]){
            // swap(arr, newNumIndex-1, newNumIndex);
            // newNumIndex--;
            // }
        }

    }
// 首先在未排序序列中找到最小（大）元素，存放到排序序列的起始位置，然后，再从剩余未排序元素中继续寻找最小（大）元素，然后放到已排序序列的末尾。
    public static void selectSort(int[] arr) {
        if (arr == null || arr.length < 2)
            return;
        int N = arr.length;
        for (int i = 0; i < N; i++) {
            int minValueIndex = i;
            for (int j = i + 1; j < N; j++) {
                minValueIndex = arr[j] < arr[minValueIndex] ? j : minValueIndex;
            }
            swap(arr, i, minValueIndex);
        }
    }

    public static void main(String args[]) {
        int maxLen = 50;
        int maxValue = 1000;
        int testTime = 10000;
        for (int i = 0; i < testTime; i++) {
            int[] arr1 = lenRandomValueRandom(maxLen, maxValue);
            int[] arr2 = copyArray(arr1);
            selectSort(arr1);
            insertionSort(arr2);
            if (!isSorted(arr1)) {
                System.out.println("排序错误");
            }
        }
        System.out.println("works!!!!");
    }
}
