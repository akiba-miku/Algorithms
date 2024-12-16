//二分答案法
//测试链接luogu: 
//测试用例:
//10 30
//15 27 9 32 29 7 7 21 8 34
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1e6+10; 
int q[N],n,m;

void bf(int l,int r){
    ll ans = INT_MIN;
    for(int i=l;i<=r;++i){
        ll sum = 0;
        for(int j=0;j<n;j++){
            sum += q[j]-i>0?q[j]-i:0;
        }
        if(sum>=m){
            ans = max(ans,(ll)i);
        }
    }
    printf("%lld\n",ans);
}

void binary_search(int l,int r){
    ll ans = 0x7fffffff;
    int k;
    //l：l锯齿上升的最小高度->它可以获得最多的木材
    //2：r锯齿上升的最大高度->它可以获得最少的木材
    //3：找出恰好满足>=m的临界高度
    while(l<=r){
        k=l+((r-l)>>1);
        ll sum = 0;
        for(int i=0;i<n;i++){
            sum += q[i]>k?q[i]-k:0;
        }
        if(sum>=m){
            ans = k;
            l = k + 1;
        }else r = k - 1;
    }
    printf("%lld\n", ans);
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++){
        scanf("%d",q+i);
    }
    int l=INT_MAX,r=INT_MIN;
    for(int i=0;i<n;i++){
        l=min(l,q[i]);
        r=max(r,q[i]);
    }
    printf("测试开始\n");
    printf("暴力解法的结果:>");
    bf(l,r);
    printf("二分答案法结果:>");
    binary_search(l,r);
    printf("\n");
    return 0;
}