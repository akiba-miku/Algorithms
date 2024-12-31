### 前言
近一个月没更新了， 今天心血来潮更新一下吧。 笔者由于最近准备期末考试， 每天敲代码和写算法题的时间大幅缩水了。 再过几天就是数据结构，算法，计网的考试了。 临近期末周， 给12月份也补上一篇吧。
本篇是图论篇的最短路径算法， 最短路径算法有很多，Bellman-Foyid， SPFA， A*. 这里先写一篇经典的**单源最短路径算法`Dijkstra算法`**。

---
### 前置知识和大致介绍
由于数据结构和离散数学都有讲Dijkstra算法， 对于基础的概念笔者默认跳过了。
读者自行熟悉一下路径和最短路径的概念， 在此我尽量减少篇幅。
**前置知识： 图论中有关最短路径的概念；邻接表，邻接矩阵，链式前向星建图（本篇主要是基于链式前向星建图）**
**编程语言:   C++/Java**
**使用提示: 可以借助ChatGPT-4o转化成对应语言的代码。 比如期末考试中的C语言代码。**
**大致内容:经典普通堆优化版本的Dijkstra算法。 因此可以执行**
Dijkstra算法是经典的最短路径算法。 它是一种动态规划和贪心的策略应用。

----
###  主要内容 
#### **一、研究最短路径的对象是什么？**  
最短路径问题研究的对象是**带权图**，但需满足以下限制：  
- **权值非负**（即所有边的权值 $\geq 0$）。  
- **图:[有向无向图均可]**

这类图模型广泛应用于路径规划、物流运输、网络流量等领域，是图论中最重要的研究对象之一。

---

#### **二、什么是最短路径？**  
这里简单回顾一下:
- 给定一个路径 $p$，其形式为：  
  $[
  p = v_1 \to v_2 \to v_3 \to \dots \to v_k  
  ]$  
  这里的 \(p\) 是一条由顶点组成的线性序列，描述了从 $v_1$ 到 $v_k$ 的连接方式。

- 每条路径的权重 \(w(p)\) 是其所经过边的权值之和：  
  $[
  w(p) = \sum_{i=1}^{k-1} w(v_i, v_{i+1})  
  ]$  

- **最短路径**即为所有从起点到终点的路径中，总权值 $w(p)$最小的那条路径。  
  **通俗定义**：  
  > 最短路径就是从起点 \(A\) 到终点 \(B\) 的距离最近的路径。  

通过经典的**Dijkstra算法**，可以高效地求解这一问题。

---

#### **三、为什么权值不能为负数？**  
权值非负是Dijkstra算法的一项核心要求，原因如下：  

1. **`负权边可能导致最短路径不存在`**  
   - 如果图中存在**负权值环**，路径上的总权值可以通过反复绕环降低至任意负值，形成无穷循环。  
     > **示例**：  
     > 若路径环 $(C = v_i \to v_j \to v_k \to v_i)$，其总权重 $(w(C) < 0)$，那么对于所有能够通往环 $(C)$ 的顶点，都无法找到一个有限的最短路径。

2. **`权值非负使贪心策略成立`**  
   - Dijkstra算法通过逐步扩展最短路径集合的方式寻找解，假设“当前最短路径一定是最终解的一部分”。这种贪心思想只有在权值非负时才能保证正确性。  

3. **`为什么负权边“可能”导致最短路径不存在`？**  
   - 如果图中仅存在单条**分散的负权边**（且无负权环），最短路径依然可能存在。例如：  
     > $(A \to B)$ 权重为 -5，但 \(B\) 无其他负权边，仍能找到最短路径。
4. **`最短路径不存在的另一种可能`**
	- 如果图中两个顶点$u,v$,它们之间是不连通的。 换言之， 它们之间不存在路径。 因此最短路径的概念不存在非连通的点之间。


引入一种数学描述$\delta(u,v): u->v的最短路径$。
它存在三种结果$\delta(u,v)=-\infty$, 
$\delta(u,v)=\infty$,
$\delta(u,v)>=0,且是一个确定的数.$
第一种情况是
总结：**有负权值环的有向图中，所有能入环的点都不存在最短路径**。
 
--- 
#### **四、什么是`Dijkstra算法`**
$dijkstra$算法是一种单源最短路径算法。
>单源最短路径：给定一个源节点， 可以求出源节点到所有可达顶点的最短距离， 对于不可达顶点认为它们的距离为$\infty$, 实际代码实现通常为系统最大值。
>
朴素算法时间复杂度:$O(m^2)$, 太过暴力， 可以大致了解一下。
普通堆优化的时间复杂度:$O(mlogm)$，这种算法时间复杂度已经比较好了，适合稀疏图(边数<顶点数）
反向索引堆的时间复杂度:$O(mlogn)$,  通过反向索引堆优化，适合稠密图。

有关时间复杂度推导会在后面部分说明。

---

#### **五、Dijkstra算法的核心原理**  
- 贪心思想的应用：通过已知节点逐步扩展已知最短路径集合
- 最短路径估计值的动态更新  
- 松弛操作（Relaxation）  

算法流程: 
1. 建图， 根据题目给定输入选择一种合理的方式建图。(竞赛选择链式前向星， LC商业平台可以邻接表， 顶点数较少选择邻接矩阵)
2. 准备三个容器， `dist数组(int)`,`visit数组（bool)`,`最小堆(数组手写堆或者C++/Java内置的优先级队列)`。
3. 初始化容器， dist数组值为$\infty$ ,visit数组为false, 创建或者清空堆。
4. 主流程: 选择一个源节点`src`, `dist[src]=0`, **dist数组含义为src->target(目标节点）当前遍历到顶点的最短路径，visit数组表示当前顶点有无被访问过(用作记忆化搜索)** 将src加入到优先队列。
5. 优先队列（最小堆）内部优先级逻辑是(源节点到当前节点的距离，距离小的优先级更高）， 如果当前优先队列不为空， 那么将这个顶点标记为已访问过执行后续步骤。 优先队列堆顶元素(记为`cur`)出队， 遍历它的所有邻居进行动态更新。
6. 动态更新的逻辑： 若`v顶点未访问过`且`dist[cur]+w<dist[v]`, w是cur->v的权值， v是cur的一个邻居。文字翻译为， 如果src到cur的最短路径+cur到v的最短路径小于src先前到v的最短路径， 那么更新这个值`dist[v]=dist[cur]+w`, 并将$\{v, dist[v]\}$加入到优先队列中。
7. 5,6是个主循环， 当优先队列为空结束。 dist数组记录的就是src到所有可达节点的最短路径。 **单源最短路径表**

如果当前src到某个节点不可达， 由第3条它会被初始化为$\infty$， 但由于不可达在第6条中它将不会得到更新。
**因此，通过Dijkstra算法可以判断源节点到某一顶点之间是否可达。只需要查询dist表中是否为∞即可**

### **代码实现**

#### LC模板(C++示例）
由于前面二已经给出了Dijkstra算法的文字流程， 只需要将上述翻译成代码即可。  
- 初始化步骤: 建图，初始化容器， 源节点的处理。
- 主循环中处理优先队列动态更新的过程。

先以LC上这道函数题为模板
[链接点击这里](https://leetcode.cn/problems/network-delay-time/)
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/2b93fa9769134beb813623fe09e193f8.png)
这道题可以很容易翻译为求当前源节点k到所有节点之间的最短距离。 该图是有向带权图， 权值是时间(必然为正数）。
以下以C++语言说明， 给定函数信息如下。
`int networkDelayTime(vector<vector<int>>& times, int n, int k)`；
1. 采用**邻接表**进行建图。
```cpp
		// 1. 建图：graph[u] 里存 (v, w)
        vector<vector<pair<int, int>>> graph(n + 1);
        for (auto& edge : times) {
            int u = edge[0], v = edge[1], w = edge[2];
            graph[u].push_back({v, w});
        }
```
2. 准备并初始化**Dijkstra算法**的visit和dist数组
```cpp
		// 2. 准备Dijkstra需要的数组
        vector<int> dist(n + 1, INT_MAX);
        vector<bool> visited(n + 1, false);
```
3. 准备小根堆， 这里以C++标准库的优先级队列为例
```cpp
		// 3. 小根堆：存储 (节点, 当前距离)
        auto cmp = [](const pair<int, int>& a, const pair<int, int>& b) {
            // a.second > b.second => 小根堆
            return a.second > b.second;
        };
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> minHeap(cmp);
```
4. 流程开始, 处理源节点k
```cpp
		// 4. 初始化：从 k 出发
        dist[k] = 0;
        minHeap.push({k, 0});
```
5. 主循环，终止条件:优先队列为空。
```cpp
		// 5. Dijkstra 主循环
        while (!minHeap.empty()) {
            auto node = minHeap.top().first;
            minHeap.pop();

            if (visited[node])
                continue;
            visited[node] = true;

            // 遍历 node 的所有邻居
            for (auto& [nxt, w] : graph[node]) {
                if (!visited[nxt] && dist[node] + w < dist[nxt]) {
                    dist[nxt] = dist[node] + w;
                    minHeap.push({nxt, dist[nxt]});
                }
            }
        }
```

6. 本题特殊处理， 如果k节点存在不可达的顶点， 那么返回-1. 否则返回k节点到某一节点简单路径的最大值。
```cpp
		// 6. 统计结果：若有不可达节点，直接返回 -1；否则返回最大距离
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            if (dist[i] == INT_MAX) {
                return -1;
            }
            ans = max(ans, dist[i]);
        }
        return ans;
```


#### C++完整实现
```cpp
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        // 1. 建图：graph[u] 里存 (v, w)
        vector<vector<pair<int, int>>> graph(n + 1);
        for (auto& edge : times) {
            int u = edge[0], v = edge[1], w = edge[2];
            graph[u].push_back({v, w});
        }

        // 2. 准备Dijkstra需要的数组
        vector<int> dist(n + 1, INT_MAX);
        vector<bool> visited(n + 1, false);

        // 3. 小根堆：存储 (节点, 当前距离)
        auto cmp = [](const pair<int, int>& a, const pair<int, int>& b) {
            // a.second > b.second => 小根堆
            return a.second > b.second;
        };
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> minHeap(cmp);

        // 4. 初始化：从 k 出发
        dist[k] = 0;
        minHeap.push({k, 0});

        // 5. Dijkstra 主循环
        while (!minHeap.empty()) {
            auto node = minHeap.top().first; // 结构化绑定(C++17)
            minHeap.pop();

            if (visited[node])
                continue;
            visited[node] = true;

            // 遍历 node 的所有邻居
            for (auto& [nxt, w] : graph[node]) {
                if (!visited[nxt] && dist[node] + w < dist[nxt]) {
                    dist[nxt] = dist[node] + w;
                    minHeap.push({nxt, dist[nxt]});
                }
            }
        }

        // 6. 统计结果：若有不可达节点，直接返回 -1；否则返回最大距离
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            if (dist[i] == INT_MAX) {
                return -1;
            }
            ans = max(ans, dist[i]);
        }
        return ans;
    }
};

```

#### Java完整实现
注释由ChatGPT生成。
同样邻接表进行建图
```java
class Solution {
    public int networkDelayTime(int[][] times, int n, int k) {
        // 1. 建图：使用 ArrayList 存储邻接表，每个元素是一个 (目标节点, 权值) 数组
        ArrayList<ArrayList<int[]>> graph = new ArrayList<>();
        
        // 初始化 graph，使得下标从 0 到 n，共 n+1 个位置
        for(int i = 0; i <= n; i++){
            graph.add(new ArrayList<>());
        }

        // 2. 准备 Dijkstra 所需的数据结构
        // dist[i] 存储从起点 k 到节点 i 的当前最短距离，初始化为最大值
        int[] dist = new int[n + 1];
        Arrays.fill(dist, Integer.MAX_VALUE);

        // visit[i] 表示节点 i 是否已经确定了最短距离（是否被“收录”）
        boolean[] visit = new boolean[n + 1];

        // 3. 将输入的边 times[] 构建到 graph 中
        // times[i] = [u, v, w] 表示边 u -> v，权重 w
        // u,v,w 各自在代码中临时存储
        int u, v, w;
        for(int[] edge : times){
            u = edge[0];
            v = edge[1];
            w = edge[2];
            // 对应节点 u 的邻接列表中，加入 (v, w)
            graph.get(u).add(new int[]{v, w});
        }

        // 4. 创建一个小顶堆 (最小优先队列)，里面存储 (节点, 与起点距离)
        // 依据距离从小到大排序
        PriorityQueue<int[]> minheap = new PriorityQueue<>((a, b) -> a[1] - b[1]);
        
        // 将起点 k 入队，初始距离为 0
        minheap.add(new int[]{k, 0});
        dist[k] = 0;

        // 5. Dijkstra 主循环：
        // 不断从最小堆中弹出距离最近的未访问节点，更新其邻居节点的距离
        while(!minheap.isEmpty()){
            // 取出堆顶元素 (u, 当前最小距离)
            u = minheap.poll()[0];
            
            // 如果该节点已被收录，跳过
            if(visit[u]){
                continue;
            }
            // 否则标记为已访问
            visit[u] = true;

            // 遍历节点 u 的所有邻居 (v, w)
            for(int[] e : graph.get(u)){
                v = e[0];
                w = e[1];
                // 若 v 尚未被收录，并且通过 u 到 v 的距离更短，则更新 dist[v]
                if(!visit[v] && dist[u] + w < dist[v]){
                    dist[v] = dist[u] + w;
                    // 将更新后的 (v, dist[v]) 推入堆
                    minheap.add(new int[]{v, dist[v]});
                }
            }
        }

        // 6. 计算结果：找出 dist[] 数组中的最大值，即最慢到达时间
        // 如果有节点仍是 Integer.MAX_VALUE，说明它不可达，返回 -1
        int ans = Integer.MIN_VALUE;
        for(int node = 1; node <= n; node++){
            if(dist[node] == Integer.MAX_VALUE){
                return -1;  // 存在不可达节点
            }
            ans = Math.max(ans, dist[node]);
        }

        // 若所有节点可达，返回最大延迟时间
        return ans;
    }
}

```

### 普通堆优化下的Dijkstra算法模板
[洛谷P4779](https://www.luogu.com.cn/problem/P4779)
静态空间， 链式前向星建图，手写普通堆。
`C++版本`
```cpp
#include <bits/stdc++.h>
using namespace std;

// ========== 常量定义 ==========
static const int MAXN = 1e5+10; // 节点上限（题意中一般为10^5）
static const int MAXM = 2e5+10; // 边的上限（题意中一般为2×10^5）

// ========== 链式前向星存图相关数组 ==========
int head[MAXN], nxt[MAXM], to_[MAXM], w[MAXM];
int cnt; // 当前边下标（从 1 开始）

// ========== Dijkstra 需要的数组 ==========
int dist_[MAXN];   // dist_[u] 表示从起点 s 到 u 的最短距离
bool visited[MAXN]; // visited[u] 表示节点 u 是否已经确定最短距离

// ========== 输入数据 ==========
int n, m, s; // n: 节点数, m: 边数, s: 起点

// ========== 初始化 ==========
void build() {
    cnt = 1;
    for(int i = 1; i <= n; i++){
        head[i]    = 0;       // 没有边
        dist_[i]   = INT_MAX; // 最短距离初始为无穷
        visited[i] = false;   
    }
}

// ========== 添加边 ==========
// 在链式前向星中，为 u 添加一条有向边 (u -> v)，权重 wgt
void add_e(int u, int v, int wgt) {
    nxt[cnt]   = head[u];
    to_[cnt]   = v;
    w[cnt]     = wgt;
    head[u]    = cnt++;
}

// ========== 手写堆结构 ==========
// heap[i][0] 存节点编号, heap[i][1] 存该节点的距离
int heapArr[MAXM][2];
int hz; // 当前堆大小

// 交换堆元素
void swap_heap(int i, int j){
    // 交换节点编号
    int tmp = heapArr[i][0];
    heapArr[i][0] = heapArr[j][0];
    heapArr[j][0] = tmp;
    // 交换距离
    tmp = heapArr[i][1];
    heapArr[i][1] = heapArr[j][1];
    heapArr[j][1] = tmp;
}

// 上浮
void push_up(int i){
    while(i > 0 && heapArr[i][1] < heapArr[(i - 1) / 2][1]){
        swap_heap(i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

// 下沉
void push_down(int i){
    int l=2*i+1;
    // 当 left 下标在堆内，说明有子节点
    while(l < hz){
        // 选出左右孩子中距离更小的
        int best = (l+1 < hz && heapArr[l+1][1] < heapArr[l][1]) 
                    ? l+1 
                    : l;
        //孩子和父亲比较
        best = heapArr[best][1]<heapArr[i][1]?best:i;
        //父亲优先级高， 那么终止下沉操作
        if(best==i){
            break;
        }
        swap_heap(best,i);
        i = best;
        l = 2*i+1;
    }
}

// ========== Dijkstra (懒更新写法) ==========
void dijkstra() {
    // 1) 起点距离设为 0
    dist_[s] = 0;

    // 2) 把起点 (节点 s, 距离 0) 放入堆
    heapArr[0][0] = s;
    heapArr[0][1] = 0;
    hz = 1; // 初始堆大小=1

    // 3) 循环
    while(hz > 0){
        // 取出堆顶
        int u = heapArr[0][0];

        // 把堆尾移到堆顶，堆大小-1
        swap_heap(0, --hz);
        push_down(0);

        // 判断是否已访问
        if(visited[u]) {
            continue;
        }
        visited[u] = true;

        // 松弛邻居
        for(int ei = head[u]; ei; ei = nxt[ei]) {
            int v = to_[ei];
            int wgt = w[ei];
            // 如果可以更新 dist_[v]
            if(!visited[v] && dist_[u] + wgt < dist_[v]) {
                dist_[v] = dist_[u] + wgt;
                // 入堆
                heapArr[hz][0] = v;
                heapArr[hz][1] = dist_[v];
                push_up(hz);
                hz++;
            }
        }
    }
}

// ========== 主函数 ==========
int main(){
    // 读入
    scanf("%d %d %d", &n, &m, &s);
    build();

    // 有向边输入
    for(int i = 0; i < m; i++){
        int u, v, wgt;
        scanf("%d %d %d", &u, &v, &wgt);
        // 只加一次 => 有向图
        add_e(u, v, wgt);
    }

    // Dijkstra
    dijkstra();

    // 输出 dist_[1]..dist_[n]
    // 注：题目若节点从1..n，这里一定要打印 dist_[1]
    printf("%d", dist_[1]);
    for(int i=2; i <= n; i++){
        printf(" %d", dist_[i]);
    }
    puts("");

    return 0;
}
```

`java版本`
```java
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

```

---

### 正确性
以下是便于理解的大致思路， 并非严格的数学推导证明~~笔者不会~~。
你的总结完全正确且清晰地描述了 Dijkstra 算法的贪心思想及其正确性！以下是对你的分析的进一步解释和补充，以更全面地展示其逻辑：

---

### 1. **贪心选择的核心思想**
$Dijkstra$是基于贪心思想实现。
核心是：在每一轮中选择当前距离源点最近的、尚未确定最短路径的节点$u$，并确定它的最短路径值。
保证以下两点
- 对于已访问到的节点， 源点到它的最短路径确定了。
- $dist[u]$是所有未确定节点中最小的，且从源点 $src$ 到$u$的路径不会被更新为更短。

### 2. **为什么未访问的节点一定不优于已访问的节点？**
在算法的每一轮：
- dis[u]最小的节点u从优先队列中取出。此时，所有未访问节点的 \( dis[v] \) 值要么等于其实际最短路径（但未被访问到），要么是尚未更新的更大值。
- 因为 \( u \) 是当前 \( dis \) 最小的节点，且边权为非负，其他未访问节点 \( v \) 不可能通过任意路径更新为比 \( dis[u] \) 更小的值。

因此：
\[
dis[v] \geq dis[u]
\]
这保证了每轮选择出的节点 \( u \) 的最短路径已经确定。

### 3. **路径更新和边权非负性**
- Dijkstra 算法的贪心性质依赖于边权非负。如果边权是非负的，则已访问节点的最短路径值 \( dis[u] \) 不可能通过任何路径再被降低。
- 若尝试通过 \( u \) 更新其邻居 \( v \) 的路径：
  \[
  dis[v] = \min(dis[v], dis[u] + w(u, v))
  \]
  这里 \( dis[u] + w(u, v) \) 的值只会降低 \( dis[v] \)，但不会影响 \( u \) 的已确定路径。

### 4. **一步一步确定最短路径**
通过贪心选择和路径更新，Dijkstra 逐步确定了从源点 \( s \) 到每个节点的最短路径：
1. 初始时，只有源点的最短路径值为 \( 0 \)，其他所有节点的路径值为 \( \infty \)。
2. 每次选择 \( dis[u] \) 最小的节点 \( u \)，并将其标记为访问过，确定它的最短路径。
3. 更新 \( u \) 的邻居节点的 \( dis[v] \) 值。
4. 重复上述步骤，直到所有节点的最短路径被确定。

---
### 结尾  
**“算法之美在于解决问题的简洁性与优雅性，而Dijkstra算法正是其中的典范之一.”**  
有关最短路径算法的题目， 有时间再写吧。