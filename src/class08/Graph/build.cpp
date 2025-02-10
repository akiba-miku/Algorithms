//建图方式
//带权图和不带权图的部分细节不同
//1. 邻接矩阵
//int graph[N][N];二维数组,行列均是点编号。
//可以用vector

//2. 常规邻接表
//vector<vector<int>> graph;//动态建图

//3. 链式前向星建图
const int N = 11;//点的最大数量
const int M = 21;//边的最大数量
int h[N],ne[M],to[M],weight[M],idx;
//h数组的下标是点编号，其余数组下标均是边编号。
//只有链式前向星需要idx记录边的使用情况，即对边进行编号。
//weight数组是记录边的权值， 只有带权图才需要这个数组。
//n是最多用到的点编号
void init(int n){
  idx = 1;//编号从1开始进行使用
  for(int i=1;i<=n;++i) h[i]=0;
}
void add(int u,int v,int w){
  ne[idx]=h[u];
  to[idx]=v;
  weight[idx]=w;
  h[u]=idx++;
}