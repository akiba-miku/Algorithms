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
        auto l = lower_bound(q,q+m,c[i]);
        auto r = upper_bound(q,q+m,c[i]);
        sum += min(abs(*l-c[i]), abs(*r-c[i]));
    }
    printf("%lld\n", sum);
    return 0;
}