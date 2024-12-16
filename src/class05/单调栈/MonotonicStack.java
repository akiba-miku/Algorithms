import java.io.BufferedReader;
import java.io.StreamTokenizer;
import java.io.PrintWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.IOException;
public class MonotonicStack{
	public static final int N = (int)1e6+10;
	public static int[] array = new int[N];
	public static int[] stack = new int[N];
	public static int r,n;
	public static int[][] ans = new int[N][2];
	public static void main(String[] args) throws IOException{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StreamTokenizer in = new StreamTokenizer(br);
		PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
		while(in.nextToken() != StreamTokenizer.TT_EOF){
			n = (int)in.nval;
			for(int i=0;i<n;++i){
				in.nextToken();
				array[i]=(int)in.nval;
			}
			//求含重复值的单调栈函数
			compute();
			for(int i=0;i<n;++i){
				out.println(ans[i][0]+" "+ans[i][1]);
			}
		}
		out.flush();
		out.close();
		br.close();
	}

	public static void compute(){
		r=0;//清栈
		int cur;
		for(int i=0;i<n;++i){
			while(r>0&&array[stack[r-1]]>=array[i]){
				cur = stack[--r];
				ans[cur][0]=r>0?stack[r-1]:-1;
				ans[cur][1]=i;
			}
			stack[r++]=i;
		}
		while(r>0){
			cur = stack[--r];
			ans[cur][0]=r>0?stack[r-1]:-1;
			ans[cur][1]=-1;
		}

		for(int i=n-2;i>=0;--i){
			if(ans[i][1]!=-1&&array[i]==array[ans[i][1]]){
				ans[i][1] = ans[ans[i][1]][1];
			}
		}
	}
} {
    
}
