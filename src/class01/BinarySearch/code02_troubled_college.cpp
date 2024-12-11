#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1e6+10;
int q[N],m,n;
int c[N];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>m>>n;
    for(int i=0;i<m;i++) cin>>q[i];
    for(int i=0;i<n;i++) cin>>c[i];
    sort(q,q+m);
    ll sum = 0;
    for(int i=0;i<n;i++){
        int l=0,r=m-1;
        int idx = -1;
        while(l<=r){
            int m=l+((r-l)>>1);
            if(q[m]>=c[i]){
                idx = m;
                r = m - 1;
            }else l = m + 1;
        }
        if(idx!=-1){
            sum += q[idx]-c[i];
        }
    }
    printf("%lld\n", sum);
    return 0;
}