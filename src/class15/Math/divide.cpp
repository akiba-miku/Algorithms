//质因数分解方法
#include<bits/stdc++.h>
using namespace std;

void divide(int n){
    for(int i=2;i<=n/i;i++){
        if(n%i==0){
            int cnt = 0;
            while(n%i==0){
                n/=i;
                cnt++;
            }
            printf("%d %d\n", i, cnt);
        }
    }
    if(n>1){
        printf("%d %d\n", n, 1);
    }
    puts("");
}
int main(){
    int n;
    cin>>n;
    for(int i=0,x;i<n;i++){
        cin>>x;
        divide(x);
    }
    return 0;
}