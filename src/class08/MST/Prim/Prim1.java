import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.StreamTokenizer;
import java.io.PrintWriter;
import java.io.OutputStreamWriter;
import java.io.IOException;

// 提交时修改类名为Main
public class Prim1 {
    public static int MAXN = 5001;
    public static int MAXM = 400001;
    public static int[] head = new int[MAXN], next = new int[MAXM], to = new int[MAXM], weight = new int[MAXM];
    public static int cnt;

    public static int n, m, nodeCnt;

    // 改写堆：需要手写，因为java不支持直接修改优先队列内部的元素
    // 另外，需要反向索引表来找点在堆中的位置。需要实现改写堆调整优先级上浮的接口。

    // 改写堆
    // [0]:点，[1]:src->该点的权值
    public static int[][] heap = new int[MAXN][2];
    public static int heapSize;
    // 反向索引表
    // where[v] = -1, 当前节点从未进入过堆
    // where[v] = -2, 当前节点已经弹出过堆，换言之，已经添加进入最小生成树中
    // where[v] = i， 当前节点在堆中位置，即实际中在heap数组的位置。
    public static int[] where = new int[MAXN];

    public static void build() {
        for (int i = 0; i <= n; i++) {
            head[i] = 0;
            where[i] = -1;
        }
        cnt = 1;
        nodeCnt = 0;
        heapSize = 0;
    }

    public static void addEdge(int u, int v, int w) {
        next[cnt] = head[u];
        to[cnt] = v;
        weight[cnt] = w;
        head[u] = cnt++;
    }

    public static void heapify(int i) {
        int l = (i << 1) + 1;
        while (l < heapSize) {
            int best = l + 1 < heapSize && heap[l + 1][1] < heap[l][1] ? l + 1 : l;
            best = heap[best][1] < heap[i][1] ? best : i;
            if (best == i) {
                return;
            }
            swap(best, i);
            i = best;
            l = (i << 1) + 1;
        }
    }

    public static int u, v, w;

    public static void swap(int i, int j) {
        int a = heap[i][0];
        int b = heap[j][0];
        where[a] = j;
        where[b] = i;
        int[] tmp = heap[i];
        heap[i] = heap[j];
        heap[j] = tmp;
    }

    public static void pop() {
        u = heap[0][0];
        w = heap[0][1];
        swap(0, --heapSize);
        heapify(0);
        where[u] = -2;
        nodeCnt++;
    }

    public static void heapInsert(int i) {
        while (i > 0 && heap[i][1] < heap[(i - 1) >> 1][1]) {
            swap(i, (i - 1) >> 1);
            i = (i - 1) >> 1;
        }
    }

    public static void addOrUpdateOrIgnore(int e) {
        v = to[e];
        w = weight[e];
        if (where[v] == -1) { // 从未进入过堆
            heap[heapSize][0] = v;
            heap[heapSize][1] = w;
            where[v] = heapSize++;
            heapInsert(where[v]);
        } else if (where[v] >= 0) { // 在堆中，尝试更新权值
            if (w < heap[where[v]][1]) {
                heap[where[v]][1] = w;
                heapInsert(where[v]);
            }
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StreamTokenizer in = new StreamTokenizer(br);
        PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));

        while (in.nextToken() != StreamTokenizer.TT_EOF) {
            n = (int) in.nval;
            in.nextToken();
            m = (int) in.nval;
            build();
            for (int i = 0; i < m; i++) {
                in.nextToken();
                u = (int) in.nval;
                in.nextToken();
                v = (int) in.nval;
                in.nextToken();
                w = (int) in.nval;
                addEdge(u, v, w);
                addEdge(v, u, w);
            }

            int ans = prim();
            out.println(nodeCnt == n ? ans : "orz");
        }

        out.flush();
        out.close();
        br.close();
    }

    public static int prim() {
        nodeCnt = 1;
        where[1] = -2; // 节点1加入最小生成树
        for (int ei = head[1]; ei > 0; ei = next[ei]) {
            addOrUpdateOrIgnore(ei);
        }
        int ans = 0;
        while (heapSize != 0) {
            pop();
            ans += w;
            for (int ei = head[u]; ei > 0; ei = next[ei]) {
                addOrUpdateOrIgnore(ei);
            }
        }
        return ans;
    }
}