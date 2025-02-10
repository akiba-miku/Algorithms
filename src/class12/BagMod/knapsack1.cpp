//01背包 每件物品仅用一次， 物品有两种可能进背包和不进背包。
//模板背这个
// 测试链接 : https://www.luogu.com.cn/problem/P1048
#include<cstdio>
#include<algorithm>
using namespace std;

const int N = 1001;
int t,n;//t背包容量,n是货物总数
int dp[N];//一维滚动数组表
int v[N],w[N];//下标均从1到n。v[i]表示第i件物品占用容量，w[i]表示第i件物品的价值

void compute(){
	for(int i=1;i<=n;i++){
		for(int j=t;j>=v[i];j--){
			dp[j] = max(dp[j], dp[j-v[i]]+w[i]);
		}
	}
}
int main(){
	//处理输入
	scanf("%d%d",&t,&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",v+i,w+i);
	}
	compute();
	printf("%d\n",dp[t]);
	return 0;
}