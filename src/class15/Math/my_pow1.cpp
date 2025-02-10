// 乘法快速幂[模版]
// 求a的b次方，对p取模的结果
// 测试链接 : https://www.luogu.com.cn/problem/P1226

//#include<iostream>
//#include<cstdio>
#include<bits/stdc++.h>
using namespace std;
#define ll long long


ll my_pow(int a,int b,int p=1e9+7){
	ll ans = 1;
	while(b){
		if(b&1) ans=ans*a%p;
   	a=(ll)a*a%p;
  	b>>=1;
	}
  return ans;
}

int main(){
	int a,b,p;
	scanf("%d%d%d",&a,&b,&p);
	printf("%d^%d mod %d=%lld\n",a,b,p,my_pow(a,b,p));
	return 0;
}