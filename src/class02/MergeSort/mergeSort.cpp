#include<bits/stdc++.h>
using namespace std;

const int N = 1e6+10;
int q[N];
int help[N];//辅助数组

//时间复杂度:$O(nlogn)$
static void merge_sort(int *q,int l,int r){
    if(l>=r) return ;
    int m = l+((r-l)>>1);
    //递归树高度O(logn)
    merge_sort(q,l,m);
    merge_sort(q,m+1,r);
    //合并O(n)
    //l,m,r
    int a=l,b=m+1,i=l;
    while(a<=m&&b<=r) help[i++]=q[a]<=q[b]?q[a++]:q[b++];
    while(a<=m) help[i++]=q[a++];
    while(b<=r) help[i++]=q[b++];
    for(i=l;i<=r;i++) q[i] = help[i];
}
int main(){
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++) scanf("%d",q+i);
    merge_sort(q,0,n-1);
    for(int i=0;i<n;i++) printf("%d ",q[i]);
    printf("\n"); 
    return 0;
}