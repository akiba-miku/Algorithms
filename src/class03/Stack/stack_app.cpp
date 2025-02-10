#include<stack>
#include<iostream>
using namespace std;//stack在C++标准库里
int main(){ 
  //创建一个栈
  //stack<类型> 变量名
  stack<int> st;
  for(int i=0;i<10;i++){
    st.push(i);//st.push(elem) 将元素elem压入栈中。
  }
  //st.empty() 栈是否为空
  cout<<st.empty()<<endl;
  //st.top()取出栈顶元素。
  cout<<st.top()<<endl;
  //st.pop();弹出栈顶元素，但不会作为函数返回值。
  st.pop();

  //不支持迭代器访问和随机访问
  //st[1];错误！！！
  /**
   for(auto x:st){
    cout<<x<<endl; 
  }
   */
  //正确的方式，从栈顶到栈顶，先访问然后依次弹出
  while(!st.empty()){
    cout<<st.top()<<endl;
    st.pop();
  } 

  //另外，st.size();栈的大小
  return 0;
}