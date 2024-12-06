#include<vector>
#include<iostream>
using namespace std;
int main(void){
    vector<int> a1;
    vector<int> a2(100);
    vector<int> a3(100,-1);

    vector<vector<int>> a4(100, vector<int> ());//初始行， 不指定列数的二维数组。

    //以a1举例
    a1.push_back(1);//在vector后面尾接一个元素， 数组长度+1
    a1.pop_back(1);//在vector后面删除一个元素，同时长度-1

    //[]
    //可以访问并修改， 同普通数组
    std::cout<<a1[0]<<'\n';


    //获取长度
    //a1.size()

    //清空向量
    //a1.clear()

    //判空
    //a1.empty()

    //改变长度
    //a1.resize()
}