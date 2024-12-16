
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;


public class code01_manacher {
    public static int MAXN = (int)(1.1e7+10);
    public static char[] ss = new char[MAXN<<1];
    public static int[] p = new int[MAXN<<1];
    public static int n;
    public static void main(String[] args) throws IOException{
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
        out.println(manacher(in.readLine()));
        out.flush();
        out.close();
        in.close();
    }
    public static int manacher(String str){
        manacherss(str.toCharArray());
        int max = 0;
        for(int i=0,c=0,r=0,len;i<n;++i){
            len = r>i?Math.min(p[2*c-i],r-i):1;
            while(i+len<n&&i-len>=0&&ss[i+len]==ss[i-len]){
                len++;
            }
            if(i+len>r){
                r=i+len;
                c=i;
            }
            max=Math.max(max, len);
            p[i] = len;
        }
        return max-1;
    }

    public static void manacherss(char[] a){
        n = a.length * 2 + 1;
        for(int i=0,j=0;i<n;i++)
        ss[i] = (i&1)==0?'#':a[j++];
    }
}
