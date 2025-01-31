

#include<cstdio>

const int N = 1e6+10;

int a[N],d[N];

int main(){
  int n,m;
  scanf("%d%d",&n,&m);
  for(int i=1;i<=n;i++){
    scanf("%d",&a[i]);
    d[i]=a[i]-a[i-1];
  }
  while(m--){
    int l,r,c;
    scanf("%d%d%d",&l,&r,&c);
    d[l]+=c;
    d[r+1]-=c;
  }
  //最后依次输出更新完的a数组
  for(int i=1;i<=n;i++){
    a[i]=a[i-1]+d[i];
    printf("%d ",a[i]);
  } 
  puts("");
  return 0;
}