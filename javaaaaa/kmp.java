import java.io.*;

class kmp {

  public static int getIndexOf(String s1, String s2) {
    if (
      s1 == null || s2 == null || s2.length() < 1 || s1.length() < s2.length()
    ) {
      return -1;
    }
    char[] str1 = s1.toCharArray();
    char[] str2 = s2.toCharArray();
    int x = 0;
    int y = 0;
    int[] next = getNextArray(str2);
    while (x < str1.length && y < str2.length) {
      if (str1[x] == str2[y]) {
        x++;
        y++;
      } else if (next[y] == -1) {
        x++;
      } else {
        y = next[y];
      }
    }
    return y == str2.length ? x - y : -1;
  }

  public static int[] getNextArray(char[] str2) {
    if (str2.length == 1) {
      return new int[] { -1 };
    }
    int[] next = new int[str2.length];
    next[0] = -1;
    next[1] = 0;
    int i = 2; //目前在那个位置上丘next
    int cn = 0;
    while (i < next.length) {
      if (str2[i - 1] == str2[cn]) { // 匹配成功
        next[i++] = ++cn;
      } else if (cn > 0) { //还能往前跳，就更新
        cn = next[cn];
      } else {
        next[i++] = 0;
      }
    }
    return next;
  }

  public static void main(String[] args)
    throws NumberFormatException, IOException {
    // int[] nextval;
    int[] next = new int[1000010];
    BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
    PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));
    int n = Integer.parseInt(bf.readLine());
    String model = bf.readLine();
    char p[] = new char[1000010];
    for (int i = 1; i <= n; i++) {
      p[i] = model.charAt(i - 1);
    }
    int m = Integer.parseInt(bf.readLine());
    String str = bf.readLine();
    char s[] = new char[1000010];
    for (int i = 1; i <= m; i++) s[i] = str.charAt(i - 1);
    for (int i = 2, j = 0; i <= n; i++) {
      while (j > 0 && p[j + 1] != p[i]) j = next[j];
      if (p[j + 1] == p[i]) j++;
      next[i] = j;
    }
    for (int i = 1, j = 0; i <= m; i++) {
      while (j > 0 && s[i] != p[j + 1]) j = next[j];
      if (s[i] == p[j + 1]) j++;
      if (j == n) {
        pw.print(i - n + " ");
        j = next[j];
      }
    }
  }
}
