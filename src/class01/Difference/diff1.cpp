/*
问题描述:
输入一个长度为n的整数序列。
接下来输入m个操作，每个操作包含三个整数 l,r,c,表示将序列中 [l,r]之间的每个数加上c。
请你输出进行完所有操作后的序列。
*/
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