import java.util.Arrays;

public class binarySearch {

  public double findMedianSortedArray(int[] nums1, int[] nums2) {
    int n = nums1.length + nums2.length;
    double a = find(nums1, nums2, 0, 0, (n + 1) / 2);
    if (n % 2 != 0) return a;
    double b = find(nums1, nums2, 0, 0, (n + 1) / 2 + 1);
    return (a + b) / 2;
  }

  public double find(int[] nums1, int[] nums2, int k1, int k2, int k) {
    if (k1 == nums1.length) return nums2[k2 + k - 1];
    if (k2 == nums2.length) return nums2[k1 + k - 1];
    if (k == 1) return nums1[k1] < nums2[k2] ? nums1[k1] : nums2[k2];
    int a = Math.min(k / 2, nums1.length - k1);
    int b = Math.min(k - a, nums2.length - k2);
    a = k - b;
    if (nums1[k1 + a - 1] < nums2[k2 + b - 1]) {
      return find(nums1, nums2, k1 + a, k2, k - a);
    } else {
      return find(nums1, nums2, k1, k2 + b, k - b);
    }
  }

  public int shipWithDays(int[] weights, int days) {
    int l = Arrays.stream(weights).max().getAsInt();
    int r = Arrays.stream(weights).sum();
    while (l < r) {
      int mid = l + r >> 1;
      if (check(weights, mid) <= days) r = mid; else l = mid + 1;
    }
    return l;
  }

  public int check(int[] nums, int k) {
    int cnt = 1, sum = 0;
    for (int num : nums) {
      if (sum + num > k) {
        cnt += 1;
        sum = num;
      } else {
        sum += num;
      }
    }
    return cnt;
  }

  // 300最长递增子序列
  public int lenghtOfLIS(int[] nums) {
    int[] len = new int[nums.length + 1];
    len[1] = nums[0];
    int ans = 1;
    for (int i = 1; i < nums.length; i++) {
      int l = binary_search(len, ans, nums[i]);
      len[l] = nums[i];
      ans = Math.max(ans, l);
    }
    return ans;
  }

  public int binary_search(int[] nums, int n, int k) {
    int l = 1, r = n + 1, mid;
    while (l < r) {
      mid = l + r >> 1;
      if (nums[mid] < k) l = mid + 1; else r = mid;
    }
    return l;
  }

  // 475 供暖器 [1,2,3,4]  [1,4]
  public int findRadius(int[] houses, int[] heaters) {
    Arrays.sort(heaters);
    int res = 0;
    for (int house : houses) {
      int l = 0, r = heaters.length - 1;
      while (l < r) {
        int mid = l + r >> 1;
        if (heaters[mid] >= house) r = mid; else l = mid + 1;
      }
      int leftTmp = l;

      l = 0;
      r = heaters.length - 1;
      while (l < r) {
        int mid = l + r >> 1;
        if (heaters[mid] <= house) l = mid; else r = mid - 1;
      }
      int rightTmp = r;
      res =
        Math.max(
          res,
          Math.min(
            Math.abs(heaters[leftTmp] - house),
            Math.abs(heaters[rightTmp] - house)
          )
        );
    }
    return res;
  }

  public boolean searchRotateArrays(int[] nums, int target) {
    if (nums.length == 0) return false;
    if (nums[0] == target) return true;

    int mid, l = 0, r = nums.length - 1, head, tail;
    while (l < r && nums[l] == nums[0]) l++;
    while (l < r && nums[r] == nums[0]) r--;
    head = l;
    tail = r;
    while (l <= r) {
      mid = l + r >> 1;
      if (nums[mid] == target) return true;
      if (nums[mid] <= nums[tail]) {
        if (target > nums[mid] && target <= nums[tail]) l = mid + 1; else r =
          mid - 1;
      } else {
        if (target < nums[mid] && target >= nums[head]) r = mid - 1; else l =
          mid + 1;
      }
    }
    return false;
  }

  public static void main(String[] args) {
    int[] nums = new int[] { -1, 0, 3, 5, 9, 12 };
    int target = 121;
    System.out.println(binarySearch.bs1(nums, target));
    System.out.println(binarySearch.bs(nums, target));
  }

  //    左闭右闭
  public static int bs(int[] num, int target) {
    int left = 0;
    int right = num.length - 1;
    while (left <= right) {
      int middle = (left + right) / 2;
      if (num[middle] > target) {
        right = middle - 1;
      } else if (num[middle] < target) {
        left = middle + 1;
      } else {
        return middle;
      }
    }
    return -1;
  }

  //   左闭右开
  public static int bs1(int[] num, int target) {
    int left = 0;
    int right = num.length;
    while (left < right) {
      int middle = (left + right) / 2;
      if (num[middle] > target) {
        right = middle;
      } else if (num[middle] < target) {
        left = middle + 1;
      } else {
        return middle;
      }
    }
    return -1;
  }
}
