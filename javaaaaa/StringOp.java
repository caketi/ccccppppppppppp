import java.util.Comparator;
import java.util.Deque;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.PriorityQueue;
import java.util.Set;

public class StringOp {
  // 128最长连续序列
  public int longestConsecutive(int[] nums){
    Set<Integer> set = new HashSet<>();
    for(int num : nums){
      set.add(num);
    }
    int longgerStreak = 0;
    for(int num : nums){
      if(!set.contains(num-1)){ //判断num是不是头部，是就进入
        int currentNum = num;
        int currentStreak = 1;
        while(set.contains(currentNum+1)){ //再判断是否存在连续的
          currentNum++;
          currentStreak++;
        }
        longgerStreak = Math.max(longgerStreak, currentStreak);
      }
    }
    return longgerStreak;
  }
  public String frequencySort(String s){
    char[] chars = s.toCharArray();
    HashMap<Character, Integer> map = new HashMap<>();
    for(char aChar : chars){
      map.put(aChar, map.getOrDefault(aChar, 0) +1);
    }
    PriorityQueue<Character> priorityQueue = new PriorityQueue<Character>(new Comparator<Character>(){
        public int compare(Character o1, Character o2){
          return map.get(o2) - map.get(o1);
        }      
    });
    String result = "";
    while(!priorityQueue.isEmpty()){
      Character poll = priorityQueue.poll();
      for(int i = 0; i <map.get(poll); i++){
        result += poll;
      }
    }
    return result;
  }
  public int longestWPI(int[] hours) {
    int sum = 0;
    int res = 0;
    HashMap<Integer, Integer> sumToIndex = new HashMap<>();
    for (int i = 0; i < hours.length; i++) {
      if (hours[i] > 8) {
        sum++;
      } else {
        sum--;
      }
      if (sum > 0) {
        res = i + 1;
      } else {
        if (!sumToIndex.containsKey(sum)) {
          sumToIndex.put(sum, i);
        }
        if (sumToIndex.containsKey(sum - 1)) {
          res = Math.max(res, i - sumToIndex.get(sum - 1));
        }
      }
    }
    return res;
  }

  class Task {

    int id = 0;
    int time = 0;
    boolean isStart = true;

    Task(String[] split) {
      id = Integer.valueOf(split[0]);
      time = Integer.valueOf(split[2]);
      isStart = split[1].equals("start");
    }
  }

  public int[] exclusiveTime(int n, List<String> logs) {
    Deque<Task> stack = new LinkedList<>();
    int[] ans = new int[n];
    for (String log : logs) {
      Task task = new Task(log.split(":"));
      if (task.isStart) {
        stack.push(task);
      } else {
        Task last = stack.pop();
        int duration = task.time - last.time + 1;
        ans[task.id] += duration;
        if (!stack.isEmpty()) {
          ans[stack.peek().id] -= duration;
        }
      }
    }
    return ans;
  }

  // "6+2x2"
  public int calculate(String s) {
    Deque<Integer> stack = new LinkedList<>();
    char preSign = '+';
    // +6+2x2
    int num = 0;
    int n = s.length();
    for (int i = 0; i < n; i++) {
      if (Character.isDigit(s.charAt(i))) {
        num = num * 10 + s.charAt(i) - '0';
      }
      if (!Character.isDigit(s.charAt(i)) && s.charAt(i) != ' ' || i == n - 1) {
        switch (preSign) {
          case '+':
            {
              stack.push(num);
              break;
            }
          case '-':
            {
              stack.push(-num);
              break;
            }
          case '*':
            {
              stack.push(stack.pop() * num);
              break;
            }
          case '/':
            {
              stack.push(stack.pop() / num);
              break;
            }
        }
        preSign = s.charAt(i);
        num = 0;
      }
    }
    int result = 0;
    while (!stack.isEmpty()) {
      result += stack.pop();
    }
    return result;
  }

  // "ab#c", "ad#c"  true
  public String backspace(String str) {
    StringBuilder stringBuilder = new StringBuilder();
    for (int i = 0; i < str.length(); i++) {
      char ch = str.charAt(i);
      if (ch == '#') {
        if (stringBuilder.length() > 0) stringBuilder.deleteCharAt(
          stringBuilder.length() - 1
        );
      } else {
        stringBuilder.append(ch);
      }
    }

    return stringBuilder.toString();
  }

  public boolean backspaceCompare(String S, String T) {
    return backspace(S).equals(backspace(T));
  }

  public boolean backspaceCompareV2(String S, String T) {
    int countS = 0, countT = 0;
    int i = S.length() - 1, j = T.length() - 1;
    while (i >= 0 || j >= 0) {
      while (i >= 0) {
        if (S.charAt(i) == '#') {
          countS++;
          i--;
        } else if (countS > 0) {
          i--;
          countS--;
        } else {
          break;
        }
      }
      while (j >= 0) {
        if (T.charAt(i) == '#') {
          countT++;
          j--;
        } else if (countT > 0) {
          j--;
          countT--;
        } else {
          break;
        }
      }
      if (i >= 0 && j >= 0) {
        if (S.charAt(i) != T.charAt(i)) return false;
      } else {
        if (i >= 0 || j >= 0) return false;
      }
      i--;
      j--;
    }
    return true;
  }
}
