#include<bits/stdc++.h>
using namespace std;
//测试链接:https://www.luogu.com.cn/problem/P1177
const int N = 1e6+10;
int q[N], n;
void insertionSort(int *q,int n){
    for(int i=1,j;i<n;i++){
        j = i - 1;
        int tmp = q[i];
        while(j>=0&&q[j]>tmp){
            q[j+1] = q[j];
            j--;
        }
        q[j+1]=tmp;
    }
}
int main(){
    scanf("%d", &n);
    for(int i=0;i<n;i++){
        scanf("%d", q+i);
    }
    insertionSort(q,n);
    for(int i=0;i<n-1;i++){
        printf("%d ",q[i]);
    }
    printf("%d\n",q[n-1]);
    return 0;
}