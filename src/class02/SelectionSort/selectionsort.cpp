#include<bits/stdc++.h>
using namespace std;
//测试链接:https://www.luogu.com.cn/problem/P1177
const int N = 1e6+10;
int q[N],n;
void selectionSort(int *q,int n){
    int min_idx = 0;
    for(int i=0;i<n-1;i++){
        min_idx = i;
        for(int j=i+1;j<n;++j){
            if(q[j]<q[min_idx]) min_idx = j;
        }
        std::swap(q[min_idx],q[i]);
    }    
}
int main(){
    scanf("%d", &n);
    for(int i=0;i<n;i++){
        scanf("%d", q+i);
    }
    selectionSort(q,n);
    for(int i=0;i<n-1;++i){
        printf("%d ",q[i]);
    }
    printf("%d\n",q[n-1]);
    return 0;
}