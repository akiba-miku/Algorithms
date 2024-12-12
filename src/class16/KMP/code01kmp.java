import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.io.IOException;

public class code01kmp {
    public static int[] DEFALUT_ARRAY = new int[]{-1,0};
    public static int[] getNextArr(String s, int n){
        if(n<=2){
            return DEFALUT_ARRAY;
        }
        int[] next = new int[n];
        next[0] = -1;
        next[1] = 0;
        for(int i=2,pre=0;i<n;){
            if(s.charAt(i-1)==s.charAt(pre)) next[i++] = ++pre;
            else if(pre>0) pre=next[pre];
            else next[i++]=0;
        }
        return next;
    }
    public static int KMP(String str, String match){
        int n = str.length(), m = match.length();
        if(n<m) return -1;
        int[] next = getNextArr(match,m);
        int i,j;
        for(i=0,j=0;i<n && j<m;){
            if(str.charAt(i)==match.charAt(j)){
                i++;
                j++;
            }else if(j==0){
                ++i;
            }else{
                j = next[j];
            }
        }
        return j==m?i-j:-1;
    }
    public static void main(String[] args) throws IOException{
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
        String str = in.readLine();
        String match = in.readLine();
        int idx = KMP(str, match);
        if(idx==-1){
            out.println("str不存在match子串");
        }else{
            out.printf("str第一次出现match子串下标:%d \n", idx);
        }
        out.flush();
        out.close();
        in.close();

    }  
}
