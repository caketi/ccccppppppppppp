public class binarySearch {

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
