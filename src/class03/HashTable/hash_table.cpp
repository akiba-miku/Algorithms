/**
 * @author: autummwhisper
 * 
 */

#include<iostream>
#include<cstring>
#include<string>
using namespace std;

//拉链法
const int N = 1e5+3;
int h[N], e[N], ne[N], idx;

//清空哈希表
void clear(){
  memset(h,-1, sizeof h);
}

//拉链法插入
void insert(int x){
  int k = (x % N + N) % N;
  e[idx] = x;
  ne[idx] = h[k];
  h[k] = idx++;
}

bool find(int x){
  int k = (x % N + N) % N;
  for(int i=h[k];i!=-1;i=ne[i]){
    if(e[i]==x) return true;
  }
  return false;
}
int main(){
  int n;
  cin>>n;
  clear();
  while(n--){
    string op;
    int x;
    cin>>op>>x;
    if(op=="I"){
      insert(x);
    }else{
      if(find(x)) cout<<"Yes"<<endl;
      else cout<<"No"<<endl;
    }
  }
  return 0;
}