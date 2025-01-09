#include<bits/stdc++.h>
using namespace std;
//测试链接:https://www.luogu.com.cn/problem/P1177
const int N = 1e6+10;//1e4数据量可以使用，>1e5会超时。
int q[N],n;

void bubbleSort(int *q,int n){
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-1-i;j++){
            if(q[j+1]<q[j]){
                swap(q[j+1], q[j]);
            }
        }
    }
}
int main(){
    scanf("%d",&n);
    for(int i=0;i<n;++i){
        scanf("%d",q+i);
    }
    bubbleSort(q,n);
    for(int i=0;i<n-1;++i){
        printf("%d ",q[i]);
    }
    printf("%d\n",q[n-1]);
    return 0;
}