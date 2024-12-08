#include<stack>
#include<iostream>
using namespace std;
int main(void){
    stack<int> stk;
    stk.push(1);
    //查看
    stk.top();
    //删除栈顶元素
    stk.pop();
    return 0;
}