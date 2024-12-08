//hello.cpp -文件名
#include<iostream>//C++标准输入输出IO
using namespace std;//使用标准库std命名空间的标识符

//主函数main
int main(void){
    //std::cout, 这里using namespace std, 在命名不冲突的情况使用std中的cout。
    cout<<"Hello,world!\n";//'\n'的作用是换行的效果， 不会显示在控制台上。
    return 0;
}

//ctrl + ` =>启动终端
//ctrl + s保存当前文件
//切换到当前hello.cpp的文件目录下
//终端键入：g++ hello.cpp
//-> 会生成一个a.out的文件， ./a.out 运行程序
//程序输出 Hello,world!


//#include<iostream> 预处理编译指令， 会将目标文件代码拷贝该文件上。