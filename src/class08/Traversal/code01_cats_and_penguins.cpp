#include<bits/stdc++.h>
using namespace std;
const int N = 1e5+10;
//链式前向星建图
int head[N],ne[N<<1],to[N<<1],ec;
bool isvisited[N];
int qe[N], l,r;

void build(int n){
    ec=1;
   // 初始化图和访问数组
    for (int i = 1; i <= n; i++) {
        head[i] = 0;
        isvisited[i] = false;
    }
}
void add_edge(int u,int v){
    ne[ec] = head[u];
    to[ec] = v;
    head[u] = ec++;
}

//限制搜索最大深度的广度优先遍历
int bfs(int st,int max_d){
    l=r=0;
    int depth=0,cnt=0;
    qe[r++] = st;
    isvisited[st]=true;
    while(l<r&&++depth<=max_d){
        int sz = r-l;
        while(sz--){
            int cur = qe[l++];
            for(int ei=head[cur];ei>0;ei=ne[ei]){
                if(!isvisited[to[ei]]){
                    qe[r++] = to[ei];
                    ++cnt;
                    isvisited[to[ei]]=true;
                }
            }
        }
    }
    return cnt;
}
int dfs(int st,int depth){
    if(depth==0) return 0;
    int cnt = 0;
    for(int ei=head[st];ei>0;ei=ne[ei]){
        if(!isvisited[to[ei]]){
            isvisited[to[ei]] = true;
            cnt += dfs(to[ei], depth-1)+1;
        }
    }
    return cnt;
}
int main(){
    int n,d;
    scanf("%d%d",&n,&d);
    build(n);
    for(int i=0,u,v;i<n-1;i++){
        scanf("%d%d",&u,&v);
        add_edge(u, v);
        add_edge(v, u);
    }
    isvisited[1] = true;
    printf("%d\n", dfs(1,d));
    return 0;
}