//三种筛质数的方法 2~n之间有哪些质数
//普通筛:O(nlogn)
//埃氏筛:O(nloglogn)
//线性筛欧拉筛:O(n)

#include<bits/stdc++.h>
using namespace std;

const int N = 1e6+10;
int primes[N], cnt;//primes质数表，cnt跟踪质数的个数。
bool st[N];//st[i]表示i是否被筛掉，i是质数为false,是合数为true.

//普通筛
void get_prime1(int n){
  cnt = 0;//重置质数表
  for(int i=2;i<=n;i++){
    if(!st[i]) primes[cnt++] = i;
    for(int j=2*i;j<=n;j+=i) st[j]=1;
  }
}

//埃氏筛
//先筛，再统计
void get_prime2(int n){
  cnt = 0;
  for(int i=2;i<=n/i;i++){
    if(st[i]) continue;
    //筛掉i的倍数，以i开始，普通筛的做法是从2开始，会重复标记
    for(int j=i*i;j<=n;j+=i){
      st[j]=1;
    }
  }
  for(int i=2;i<=n;i++){
    if(!st[i]){
      primes[cnt++]=i;
    }
  }
}

//线性筛
void get_prime3(int n){
  cnt = 0;
  for(int i=2;i<=n;i++){
    if(!st[i]) primes[cnt++]=i;
    for(int j=0;primes[j]<=n/i;j++){
      st[i*primes[j]]=1;
      if(i%primes[j]==0) break;
    }
  }
}
int main(){
  int n;
  cin>>n;
  // get_prime1(n);
  // cout<<cnt<<endl;
  // get_prime2(n);
  // cout<<cnt<<endl;
  get_prime3(n);
  cout<<cnt<<endl;
  return 0;
}