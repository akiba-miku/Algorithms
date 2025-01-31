#include<cstdio>

const int N = 1e3+10;
int a[N][N],b[N][N];

int main(){
  int n,m,q;
  scanf("%d%d%d",&n,&m,&q);
  for(int i=1;i<=n;i++){
    for(int j=1;j<=m;j++){
      scanf("%d",&a[i][j]);
      //自己:前缀和i,j-左-上+左上
      //二维前缀和公式变形
      b[i][j]=a[i][j]-a[i][j-1]-a[i-1][j]+a[i-1][j-1];
    }
  }
  //处理q次查询
  while(q--){
    int x1,y1,x2,y2,c;
    scanf("%d%d%d%d%d",&x1,&y1,&x2,&y2,&c);
    //对原数组进行区间更新
    b[x1][y1]+=c,b[x2+1][y1]-=c,b[x1][y2+1]-=c,b[x2+1][y2+1]+=c;
  }

  //更新并输出a数组
  for(int i=1;i<=n;i++){
    for(int j=1;j<=m;j++){
      a[i][j]=b[i][j]+a[i-1][j]+a[i][j-1]-a[i-1][j-1];
      printf("%d ",a[i][j]);
    }
    puts("");
  }
  return 0;
}