#include<bits/stdc++.h>
using namespace std;

//数据范围
#define MAXN 5001
#define MAXM 400001

//读入输入的变量
int n,m;

//带权图链式前向星的模板
int head[MAXN], ne[MAXM], to[MAXM],weight[MAXM];
int cnt;

//改写堆和反向索引表
//where[i]=-1,表示i位置的顶点未加入堆中
//where[i]=-2,表示i位置顶点已经出堆了。
//where[i]>=0,表示i位置顶点在堆上，位置是heap数组中的where[i]
int heap[MAXN][2], where[MAXN];
int heapSize, nodeCnt; //nodeCnt是处理节点的个数


//base 建图，初始化堆，初始化反向索引表
void build(){
    cnt = 1;
    heapSize = nodeCnt = 0;
    for(int i=1;i<=n;i++){
        head[i] = 0;
        where[i] = -1;
    }
}

void add_edge(int u,int v,int w){
    ne[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}
//交换堆中i，j位置； 反向索引表对应也要交换，
static void swap_heap(int i,int j){
    int a =heap[i][0];
    int b =heap[j][0];
    where[a] = j;
    where[b] = i;
    int tmp_to = heap[i][0], tmp_q = heap[i][1];
    heap[i][0] = heap[j][0], heap[i][1] = heap[j][1];
    heap[j][0] = tmp_to, heap[j][1] = tmp_q;
} 
static void heapify(int i){
    //左孩子
    int l = (i<<1)+1;
    while(l<heapSize){
        //左和右
        int best = l+1<heapSize&&heap[l+1][1]<heap[l][1]?l+1:l;
        //父与子
        best = heap[best][1]<heap[i][1]?best:i;
        //决出胜负发现父亲是最强的， 不用交换
        if(best==i){
            return ;
        }
        //交换并更新
        swap_heap(best,i);
        i = best;
        l = (i<<1)+1;
    }
}
int u,w;
static void pop(){
    //取出堆顶元素
    u = heap[0][0];
    w = heap[0][1];
    //原先堆顶挪至尾部， 堆整体大小--
    swap_heap(0, --heapSize);
    //下沉调堆
    heapify(0);
    //更新索引
    where[u] = -2;
    nodeCnt++;
}

static void heapInsert(int i){
    //这里仅仅只有上浮调整， 非常简洁的写法。
    while(heap[i][1]<heap[(i-1)>>1][1]){
        swap_heap(i,(i-1)>>1);
        i = (i-1)>>1;
    }
}

//要么更新，要么添加入堆，要么无视。
//传参是边ei
static void add_update_ignore(int ei){
    int v = to[ei];
    int w = weight[ei];
    if(where[v]==-2){
        return;
    }else if(where[v]==-1){
        //尾插+上浮
        heap[heapSize][0] = v;
        heap[heapSize][1] = w;
        where[v] = heapSize++;
        heapInsert(where[v]);
    }else if(where[v]>=0){
        //调整优先级
        //由于小根堆且优先级调低， 因此上浮调整。
        heap[where[v]][1] = min(heap[where[v]][1], w);
        heapInsert(where[v]);
    }
}
//反向索引表+手写堆 优化的Prim算法
//时间复杂度:$O(n+m)+O((m+n)*logn)$
static int prim(){
    nodeCnt = 1;
    where[1] = -2;
    for(int ei = head[1]; ei > 0 ; ei = ne[ei]){
        add_update_ignore(ei);
    }
    int ans = 0;
    //堆为空则结束。
    while(heapSize!=0){
        pop();
        ans += w;
        for(int ei = head[u];ei > 0;ei = ne[ei]){
            add_update_ignore(ei);
        }
    }
    return ans;
}
int main(void){
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    cin>>n>>m;
    build();
    int u,v,w;
    for(int i=0;i<m;i++){
        cin>>u>>v>>w;
        add_edge(u,v,w);
        add_edge(v,u,w);
    }
    int ans = prim();
    if(nodeCnt!=n){
        puts("orz");
    }else{
        printf("%d\n", ans);
    }
    return 0;
}