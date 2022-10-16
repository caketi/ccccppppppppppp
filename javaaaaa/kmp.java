import java.io.*;

class kmp{
    public static void main(String[] args) throws NumberFormatException, IOException{
        // int[] nextval;
        int[] next = new int[1000010];
        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));
        int n = Integer.parseInt(bf.readLine());
        String model = bf.readLine();
        char p[] = new char[1000010];
        for(int i = 1; i<=n; i++){
            p[i] = model.charAt(i-1);
        } 
        int m = Integer.parseInt(bf.readLine());
        String str = bf.readLine();
        char s[] = new char[1000010];
        for(int i =1;i <= m; i++) s[i] = str.charAt(i-1);
        for(int i =2, j = 0; i <= n; i++){
            while(j > 0 && p[j+1] != p[i]) j  = next[j];
            if(p[j+1] == p[i]) j++;
            next[i] =j;
        }
        for(int i =1, j =0; i<=m; i++){
            while(j >0 && s[i] != p[j+1]) j=next[j];
            if(s[i] == p[j+1]) j++;
            if(j == n){
                pw.print(i-n+" ");
                j = next[j];
            }
        }
    }
    
}