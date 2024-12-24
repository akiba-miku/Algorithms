#include<bits/stdc++.h>
using namespace std;
const int N = 1001;
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
    return 0;
}