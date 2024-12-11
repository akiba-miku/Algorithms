//快速排序模板
//1. 朴素快排
//2. 三向切分快排速度
#include<bits/stdc++.h>
using namespace std;
const int N = 1e6+1;
int n, q[N];

//朴素快速排序: 一维数组或者二维数组。 
//vector， array部分排序等等。
//固定取左端点的数
void quick_sort_class(int *q,int l,int r){
    if(l>=r) return ;
        int x = q[l], i=l-1, j=r+1;
        while(i<j){
            do i++; while(q[i]<x);
            do j++; while(q[j]>x);
            if(i<j) swap(q[i],q[j]);
        }
    quick_sort_class(q,l,j);
    quick_sort_class(q,j+1,r);
}

//三向切分快排
int first ,last;
//int* q
static void quick_sort(vector<int>& q,int l,int r){
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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        scanf("%d",q+i);
    }
    quick_sort_class(q,0,n-1);
    for(int i=0;i<n;i++){
        printf("%d ", q[i]);
    }
    printf("\n");
    return 0;
}