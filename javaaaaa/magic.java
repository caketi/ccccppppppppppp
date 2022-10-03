import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

class magic {

  public static List<Integer> pancakeSort(int[] arr) {
    ArrayList<Integer> result = new ArrayList<>();
    for (int i = arr.length; i > 0; i--) {
      int index = 0; //本轮最大值索引
      while (arr[index] != i) { //本轮最大值索引要在对应的位置，如果是3就在3号位，不在找
        index++;
      }
      if (index == i - 1) {
        continue;
      } else if (index == 0) { //本轮最大值在头部，反转到它对应的位置i
        reverse(arr, i);
        result.add(i);
      } else { //换到头，再换到对应
        reverse(arr, index + 1);
        result.add(index + 1);
        reverse(arr, i);
        result.add(i);
      }
    }
    return result;
  }

  public static void reverse(int[] arr, int index) {
    int start = 0, end = index - 1;
    while (start < end) {
      int tmp = arr[end];
      arr[end] = arr[start];
      arr[start] = tmp;
      start++;
      end--;
    }
 }

  //  先找到最大值，反转到数组头部，再将其反转到钙元素排序后的位置。。 重复操作
  // 收入5，10， 20-- 成本5
  public boolean lemonadeChange(int[] bills) {
    int five = 0, ten = 0;
    for (int bill : bills) {
      if (bill == 5) {
        five++;
      } else if (bill == 10) {
        if (five == 0) return false;
        five--;
        ten++;
      } else {
        if (five > 0 && ten > 0) {
          five--;
          ten++;
        } else if (five >= 3) {
          five -= 3;
        } else {
          return false;
        }
      }
    }
    return true;
  }

  public boolean specialJudge(String a, String b) {
    int[] count = new int[26];
    for (int i = 0; i < a.length(); i++) {
      count[a.charAt(i) - 'a']++;
    }
    for (int c : count) {
      if (c > 1) return true;
    }

    return false;
  }

  public boolean buddyStrings(String a, String b) {
    if (a.length() != b.length()) return false;
    if (a.equals(b)) return specialJudge(a, b);
    int first = -1, second = -1;
    for (int i = 0; i < a.length(); i++) {
      if (a.charAt(i) != b.charAt(i)) {
        if (first == -1) {
          first = i;
        } else if (second == -1) {
          second = i;
        } else {
          return false;
        }
      }
    }
    return (
      second != -1 &&
      a.charAt(second) == b.charAt(first) &&
      a.charAt(first) == b.charAt(second)
    );
  }

  public static int getKthMagicNumber(int k) {
    int[] numbers = new int[k];
    numbers[0] = 1;
    int p3 = 0, p5 = 0, p7 = 0;
    for (int i = 1; i < k; i++) {
      numbers[i] =
        Math.min(Math.min(3 * numbers[p3], 5 * numbers[p5]), 7 * numbers[p7]);
      if (numbers[i] == 3 * numbers[p3]) p3++;
      if (numbers[i] == 5 * numbers[p5]) p5++;
      if (numbers[i] == 7 * numbers[p7]) p7++;
    }
    return numbers[k - 1];
  }

// 最短耗时-- (len(A)-1) *(n+1) + m
// len(A)任务数最多的次数，n-同任务的等待时间，m表示最多任务数的种类
// 任务总数>最短耗时，最终耗时为任务总数
// 任务总数<最短耗时，最短耗时
public int leastInterval(char[] tasks, int n){
    int[] count = new int[26];
    for(int i = 0; i < tasks.length; i++){
        count[tasks[i] - 'A']++;
    }
    Arrays.sort(count);
    int maxTimes = count[25];
    int maxCount = 1;
    for(int i = 25; i >=1 && count[i] == count[i-1];i--, maxCount++);
    return Math.max((maxTimes-1)*(n+1) + maxCount, tasks.length);
}

  public static void main(String args[]) {
    // magic m = new magic();
    // boolean mRes = m.buddyStrings("abcd", "adcb");
    // System.out.println(mRes);
    // int res = getKthMagicNumber(40);
    // System.out.println(res);
    magic m = new magic();
    char[] in = {'A','A','B'};
   
    System.out.println(m.leastInterval(in, 1));
    System.out.println(m.leastInterval(in, 2));

  }
}
