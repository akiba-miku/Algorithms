import java.io.BufferedReader;
import java.io.StreamTokenizer;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.io.IOException;

//测试链接:https://www.luogu.com.cn/problem/P4779
//提交时修改主类名为Main
public class Dijkstra {
    public static final int MAXN = (int)1e5 + 10;
    public static final int MAXM = (int)2e5 + 10;

    // ========== 读取输入相关 ==========
    public static int n, m, s;             // n:节点数, m:边数, s:起点

    // ========== 链式前向星存图 ==========
    public static int[] head  = new int[MAXN];
    public static int[] next  = new int[MAXM];
    public static int[] to    = new int[MAXM];
    public static int[] weight = new int[MAXM];
    public static int cnt;

    // ========== Dijkstra 需要的辅助 ==========
    public static int[] dist   = new int[MAXN];
    public static boolean[] visited = new boolean[MAXN];

    // ========== 小顶堆结构 (heapArr[i][0] = 节点编号, heapArr[i][1] = 距离) ==========
    public static int[][] heapArr = new int[MAXM][2];
    public static int heapSize;

    // ========== 初始化 ==========
    public static void build() {
        cnt = 1;
        for(int i = 0; i <= n; i++){
            head[i] = 0;
            visited[i] = false;
            dist[i] = Integer.MAX_VALUE;
        }
        heapSize = 0;
    }

    // ========== 添加一条 (u->v) 的有向边，权重 wgt ==========
    public static void addEdge(int u, int v, int wgt){
        next[cnt]    = head[u];
        to[cnt]      = v;
        weight[cnt]  = wgt;
        head[u]      = cnt++;
    }

    // ========== 交换堆中两个位置 ==========
    public static void swap(int i,int j){
        int[] tmp   = heapArr[i];
        heapArr[i]  = heapArr[j];
        heapArr[j]  = tmp;
    }

    // ========== “上浮”操作：对下标 i 的元素进行向上调整 ==========
    public static void push_up(int i){
        while(heapArr[i][1] < heapArr[(i - 1) / 2][1]){
            swap(i, (i - 1) / 2);
            i = (i - 1) / 2;
        }
    }

    // ========== “下沉”操作：对下标 i 的元素进行向下调整 ==========
    //这里实际上仅对堆顶做下沉操作， 故而可以如下方式写
    public static void push_down(){
        int i = 0;
        int l = 1;
        while(l < heapSize){
            // 先比较左右孩子，选出更小的
            int r = l + 1;
            int best = (r < heapSize && heapArr[r][1] < heapArr[l][1])
                    ? r : l;
            // 再与父节点比较
            if(heapArr[best][1] < heapArr[i][1]){
                swap(best, i);
                i = best;
                l = i * 2 + 1;
            } else {
                break;
            }
        }
    }

    // ========== Dijkstra (懒更新写法) ==========
    public static void dijkstra(){
        // 1) 起点距离设为0，堆中插入 (s, 0)
        dist[s] = 0;
        heapArr[0][0] = s;
        heapArr[0][1] = 0;
        heapSize = 1;

        // 2) 主循环
        while(heapSize > 0){
            // 取出堆顶 (u, curDist)
            int u = heapArr[0][0];
            // 移除堆顶 => 将堆尾移到顶，再“下沉”
            swap(0, --heapSize);
            if(heapSize > 0) {
                push_down(0);
            }

            // 如果已访问过，跳过
            if(visited[u]) {
                continue;
            }
            // 标记 u 已确定最短距离
            visited[u] = true;

            // 3) 用 u 去松弛邻居 v
            for(int ei = head[u]; ei > 0; ei = next[ei]){
                int v = to[ei];
                int wgt = weight[ei];
                // 若可以松弛
                if(!visited[v] && dist[u] + wgt < dist[v]){
                    dist[v] = dist[u] + wgt;
                    // 插入到堆的末尾，令其“上浮”
                    heapArr[heapSize][0] = v;
                    heapArr[heapSize][1] = dist[v];
                    push_up(heapSize);
                    heapSize++;
                }
            }
        }
    }

    // ========== 主函数 ==========
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StreamTokenizer in = new StreamTokenizer(br);
        PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));

        // 如果题目有多组测试，就用 while(in.nextToken() != ...) 包一层循环
        while(in.nextToken() != StreamTokenizer.TT_EOF){
            n = (int)in.nval;
            // 初始化
            build();

            in.nextToken(); m = (int)in.nval;
            in.nextToken(); s = (int)in.nval;

            // 读入 m 条边
            for(int i=0,u,v,wgt; i < m; i++){
                in.nextToken(); u   = (int)in.nval;
                in.nextToken(); v   = (int)in.nval;
                in.nextToken(); wgt = (int)in.nval;
                addEdge(u, v, wgt);
            }

            // 执行 Dijkstra
            dijkstra();

            // 输出 dist[1..n]
            out.print(dist[1]);
            for(int i = 2; i <= n; i++){
                out.print(" " + dist[i]);
            }
            out.println();
        }

        out.flush();
        br.close();
        out.close();
    }
}

