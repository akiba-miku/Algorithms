#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int N = 1001, M = 2 * N;
int n, m;
int h[N], ne[M], to[M], weight[M], idx;

bool st[N];//记忆化搜索
void init(){
  idx=1;
  memset(h,0,sizeof h);
}

void dfs(int u){
  st[u]=1;
  for(int e=h[u];e!=0;e=ne[e]){
    int v=to[e];
    if(!st[v]) dfs(v);
  }
}

int main(){
  //input...
  return 0;//
}