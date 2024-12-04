#include<bits/stdc++.h>
using namespace std;

bool is_prime(int n){
    //优化方法
    if(n<2) return false;
    //>=2的正整数
    for(int i=2;i<=n/i;i++){
        if(n % i == 0){
            return false;
        }
    }
    return true;
}
int main(){
    int n = 0;
    printf("输入一个>2的数字:->");
    scanf("%d",&n);
    printf("%d是质数吗?->%s",n,(is_prime(n)?"Yes":"No"));
    puts("");
    return 0;
}