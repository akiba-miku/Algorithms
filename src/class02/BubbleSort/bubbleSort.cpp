#include<bits/stdc++.h>
using namespace std;
const int N = 1001;
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
    return 0;
}