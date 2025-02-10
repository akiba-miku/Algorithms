//https://www.luogu.com.cn/problem/P1803
#include<bits/stdc++.h>
using namespace std;

const int N = 1e6+10;
vector<pair<int,int>> a(N);
int main(){
    int n;
    scanf("%d", &n);
    for(int i=0;i<n;i++){
        scanf("%d%d", &a[i].first, &a[i].second);
    }
    int last_end = -1;
    int event_cnts = 0;
    auto cmp_end = [](pair<int,int>& x,pair<int,int>& y){
        return x.second<y.second;
    };
    sort(a.begin(),a.begin()+n,cmp_end);
    for(int i=0;i<n;i++){
        if(a[i].first>=last_end){
            event_cnts++;
            last_end = a[i].second;
        }
    }
    printf("%d\n", event_cnts);
    return 0;
}
