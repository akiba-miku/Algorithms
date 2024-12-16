#include<stdio.h>
#define ll long long
int main(){
    ll l=0,r=202420242024*20;
    ll ans = 0;
    while(l<=r){
        int m = (l+((r-l)>>1));
        if(m/20+m/24-m/120>=202420242024){
            ans = m;
            r = m - 1;
        }else l = m + 1;
    }
    printf("%lld\n", ans);
    return 0;
}