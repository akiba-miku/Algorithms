/*
1.背景
Roy 和 October 两人在玩一个取石子的游戏。
2.描述
游戏规则是这样的：共有 $n$ 个石子，两人每次都只能取 $p^k$ 个（ $p$ 为质数，$k$ 为自然数，且 $p^k$ 小于等于当前剩余石子数），谁取走最后一个石子，谁就赢了。
现在 October 先取，问她有没有必胜策略。
若她有必胜策略，输出一行 `October wins!`；否则输出一行 `Roy wins!`。

判断标准 若初始石子n满足6k，那么后手赢，先手赢。
*/
//测试链接:https://www.luogu.com.cn/problem/P4018
#include<cstdio>
using namespace std;
int t,n;//t测试用例，n初始石头总数

//思路，~~经观察~~任何质数的幂都不可能是6的整数倍
//但是可以取得1，2，3，4，5这些数。问题归为博弈论中的巴什博弈。这是变种之一。 
int main(void){
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        printf("%s\n",(n%6!=0?"October wins!":"Roy wins!"));
    }
    return 0;
}