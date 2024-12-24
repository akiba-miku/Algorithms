#include<bits/stdc++.h>
using namespace std;
const int N = 1001;
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
    return 0;
}