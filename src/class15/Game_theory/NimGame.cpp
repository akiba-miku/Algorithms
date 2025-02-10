//Nim博弈

//思路：根据初始n堆石头数量的异或和判断先手是否必胜
// 若异或和不为0则先手胜利，反之后手胜利。
#include<cstdio>

using namespace std;
int t,n,x,eor;
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        eor = 0;
        while(n--){
          scanf("%d",&x);
          eor ^= x;
        }
        if(eor!=0){
            puts("Yes");
        }else{
            puts("No");
        }
    }
    return 0;
}