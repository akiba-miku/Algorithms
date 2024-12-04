#include<bits/stdc++.h>
using namespace std;

void divide(int n){
    for(int i=2;i<=n;i++){
        if(n%i==0){
            int cnt = 0;
            while(n%i==0){
                n/=i;
                cnt++;
            }
            printf("%d,cnt:%d\n", i, cnt);
        }
    }
    if(n>1){
        printf("%d,cnt:%d\n", n, 1);
    }
}
int main(){
    int n;
    cin>>n;
    divide(n);
    return 0;
}