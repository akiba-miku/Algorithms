//n的二进制位状态
//(n>>i)&1 获取第i位的状态
//n & (-n) 提取最低位出现的1以及后面的0
//n & (n-1) 去掉最低位的1


// #include<bits/stdc++.h>

// int main(){
//   int x = 0b101010;
//   x = x & (-x);//=>x的二进制表示为0b1 最低位的1以及后面的0被提取出来了。
//   return 0;
// }

#include<bits/stdc++.h>
using namespace std;

int main(){
    int n,x;
    scanf("%d",&n);
    while(n--){
        scanf("%d",&x);
        int cnt = 0;
        while(x){
            x = x & (x-1);
            ++cnt;
        }
        printf("%d ",cnt);
    }
    puts("");
    return 0;
}