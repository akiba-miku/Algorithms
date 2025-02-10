// 完全背包(模版)
// 给定一个正数t，表示背包的容量
// 有m种货物，每种货物可以选择任意个
// 每种货物都有体积costs[i]和价值values[i]
// 返回在不超过总容量的情况下，怎么挑选货物能达到价值最大
// 返回最大的价值
// 测试链接 : https://www.luogu.com.cn/problem/P1616
// 本题必须严格空间压缩且必须开64位整型 C++ long long(最后一个测试用例int会溢出)
//dp[i][j]：1-i号商品，每种商品可以无限拿，容量不超过j，最大价值。

//转移方程
//1. dp[i][j]->dp[i-1][j]。完全不要i
//2. 枚举拿1到恰好不超过j容量的情况。
// dp[i][j]->dp[i-1][j-v[i]]+w[i]->通解：dp[i-1][j-v[i]*cnt]+cnt*w[i];
// 不需要枚举cnt，只需要取出dp[i][j-v[i]]+w[i]即可。这就是与01背包的区别。

#include<cstdio>
#include<algorithm>
using namespace std;

const int N = 1e7+10;//二维写法20001左右
int t,n;//t背包容量，n是货物总数。
int v[N],w[N];//v[i]表示第i号货物的占用容量，w[i]表示第i号货物的价值。

// 二维状态递推写法
// int dp[N][N];

// void compute1(){
// 	for(int i=1;i<=n;i++){
// 		for(int j=0;j<=t;j++){
//        dp[i][j]=dp[i-1][j];
// 			  if(j-v[i]>=0){
// 			    dp[i][j]=max(dp[i][j],dp[i][j-v[i]]+w[i]);
// 			  }
// 		}
// 	}
// }

long long dp2[N];
void compute2(){
	for(int i=1;i<=n;i++){
		for(int j=v[i];j<=t;j++){
			dp2[j]=max(dp2[j],dp2[j-v[i]]+w[i]);
		}
	}
}
int main(){
	scanf("%d%d",&t,&n);
 	for(int i=1;i<=n;i++){
		scanf("%d%d",v+i,w+i);
	}
//	compute1();
//	printf("%d\n",dp[n][t]);
	compute2();
	printf("%lld\n",dp2[t]);
	return 0;
}