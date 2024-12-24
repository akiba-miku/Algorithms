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


