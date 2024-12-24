//测试链接:https://www.luogu.com.cn/problem/P5788

#include<bits/stdc++.h>
using namespace std;
const int N = 3e6+10;
int q[N],n;
int stack_arr[N], r=0;
vector<int> ans(N);
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>q[i];
    }
    for(int i=1;i<=n;i++){
        while(r>0&&q[stack_arr[r-1]]<q[i]){
            ans[stack_arr[--r]] = i;
        }
        stack_arr[r++] = i;
    }
    
    
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<" ";
    }
    cout<<endl;
    return 0;
}