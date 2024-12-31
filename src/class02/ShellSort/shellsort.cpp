#include<bits/stdc++.h>
using namespace std;
const int N = 1e6+10;
int q[N],n;

void shellSort(int *q, int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = q[i];
            int j = i - gap;
            while (j >= 0 && q[j] > temp) {
                q[j+gap] = q[j];
                j -= gap;
            }
            q[j+gap] = temp;
        }
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>q[i];
    }
    shellSort(q,n);
    for(int i=0;i<n-1;i++){
        cout<<q[i]<<" ";
    }
    cout<<q[n-1]<<'\n';
    return 0;
}