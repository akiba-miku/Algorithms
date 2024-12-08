import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.StreamTokenizer;
import java.io.PrintWriter;
import java.io.OutputStreamWriter;
import java.io.IOException;

public class Prim1{
    public static int MAXN = 5001;
    public static int MAXM = 400001;
    public static int[] head = new int[MAXN], next = new int[MAXM], to = new int[MAXM];
    public static int cnt;

    public static void build(int n){
        for(int i=0;i<=n;i++){
            head[i] = 0;
        }
        cnt = 1;
    }
    public static void addEdge(int u,int v,int w){
        next[cnt] = head[u];
        to[cnt] = v;
        weight[cnt] = w;
        head[u] = cnt++;
    }

    //改写堆： 需要手写， 因为java不支持直接修改优先队列内部的元素
    //另外，需要反向索引表来找点在堆中的位置。 需要实现改写堆调整优先级上浮的接口。

    public static void main(String[] args) throws IOException{
        BufferedReader
    }

}
