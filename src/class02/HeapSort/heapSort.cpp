#include<bits/stdc++.h>
using namespace std;
//测试链接:https://www.luogu.com.cn/problem/P1177
const int N = 1e6+10;
int q[N],n;

void heapify(int *q,int size,int i){
    int l=i*2+1;
    while(l<size){
        int best = l+1<size&&q[l+1]>q[l]?l+1:l;
        best = q[best]>q[i]?best:i;
        if(best==i) return ;
        std::swap(q[i],q[best]);
        i = best;
        l = i*2+1;
    }
}
int main(){
    scanf("%d", &n);
    for(int i=0;i<n;i++){
        scanf("%d", &q[i]);
    }
    for(int i=(n-1)>>1;i>=0;i--){
        heapify(q,n,i);
    }
    int size = n;
    while(size>0){
        swap(q[0],q[--size]);
        heapify(q,size,0);
    }
    for(int i=0;i<n-1;i++){
        printf("%d ",q[i]);
    }
    printf("%d\n",q[n-1]);
    return 0;
}
// int main(){
//     scanf("%d", &n);
//     //借助大根堆/最大优先队列排序
//     priority_queue<int> pq;
//     for(int i=0;i<n;i++){
//         scanf("%d", q+i);
//         pq.push(q[i]);
//     }
//     for(int i=n-1;i>=0;i--){
//         q[i] = pq.top();
//         pq.pop();
//     }
//     return 0;
// }