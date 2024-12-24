#include<bits/stdc++.h>
using namespace std;
const int N = 1e6+10;
int q[N];

void shellSort(int *q,int n){
    for(int gap=n/2;gap>0;gap/=2){
        for(int i=gap;i<n;i+=gap){
            int j=i-gap;
            int temp = q[i];
            while(j>=0&&q[j]>temp){
                q[j+gap]=q[j];
                j -= gap;
            }
            q[j+gap]=temp;
        }
    }
}
int main(){
    int n;
    cout<<"输入数组长度->";
    cin>>n;
    cout<<"输入测试数据:";
    for(int i=0;i<n;i++){
        cin>>q[i];
    }
    cout<<"打印数组数据"<<endl;
    for(int i=0;i<n;i++){
        cout<<q[i]<<" ";
    }
    cout<<"\n希尔排序开始"<<endl;
    shellSort(q,n);
    cout<<"排序结束"<<endl;
    cout<<"打印观察测试结果"<<endl;
    for(int i=0;i<n;i++){
        cout<<q[i]<<' ';
    }
    cout<<'\n';
    return 0;
}