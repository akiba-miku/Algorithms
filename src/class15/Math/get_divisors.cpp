//求一个数x的所有约数集合
#include<bits/stdc++.h>
using namespace std;

//求一个数x的所有约数，按有序存储组织。
vector<int> get_divisors(int x){
  vector<int> ans;
  for(int i=1;i<=x/i;i++){
    if(x%i==0){
      ans.push_back(i);
      if(i!=x/i) ans.push_back(x/i);
    }
  }
  //排序
  sort(ans.begin(), ans.end());
  return ans;
}
int main(){
  int n;
  cin>>n;
  while(n--){
    int x;
    cin>>x;
    auto ans = get_divisors(x);
    for(auto& t: ans){
      cout<<t<<' ';
    }
    cout<<endl;
  }
  return 0;
}