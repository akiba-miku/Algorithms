//快速排序模板
//1. 朴素快排和随机化快排
//2. 三向切分快排速度
#include<bits/stdc++.h>
using namespace std;
//测试链接:https://www.luogu.com.cn/problem/P1177
const int N = 1e6+10;
int n, q[N];


void quick_sort_class(int *q,int l,int r){
    if(l>=r) return ;
    int x = q[l+rand()%(r-l+1)];//q[l]随机取左区间的数
    int i=l-1, j=r+1;
    while(i<j){
        do i++; while(q[i]<x);
        do j--; while(q[j]>x);
        if(i<j) swap(q[i],q[j]);
    }
    quick_sort_class(q,l,j);
    quick_sort_class(q,j+1,r);
}

//三向切分快排，应对大量重复值的情况。
int first ,last;
//int* q
static void quick_sort(int* q,int l,int r){
    if(l>=r) return ;
    int x = q[l+rand()%(r-l+1)];
    first=l-1,last=r+1;
    int i=l;
    while(i<last){
        if(q[i]==x) i++;
        else if(q[i]<x) swap(q[++first],q[i++]);
        else swap(q[--last],q[i]);
    }
    quick_sort(q,l,first);
    quick_sort(q,last,r);
}

int main(){
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",q+i);
    }
    quick_sort_class(q,0,n-1);//60分，会超时。随机化取数:100分
    //quick_sort(q,0,n-1);//三向切分
    for(int i=0;i<n-1;i++){
        printf("%d ", q[i]);
    }
    printf("%d\n",q[n-1]);
    return 0;
}