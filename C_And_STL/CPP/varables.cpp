#include<iostream>
using namespace std;

//标识符
//字母，数字，下划线。不能以数字开头， 如 1a这种方式命名
//C11可以用中文名为变量， 取决于编译环境

//声明变量：告诉编译器变量类型和变量名称（标识符）
//定义变量：给变量分配内存， 多数情况两者同时发生。

//常量
//1，2 0x1A 032 0b11011010  整数常量可以以10,16,8,2进制。
//0.5 1.0  2.6f 1.6e2 12e-1 .26E1f
//'a','e' 97 '\x60' '\100' 字符类型可以 单引号内套字符， ASCII码 \+16进制或者8进制
//true false bool类型
//"jo"

//使用#define预处理指令
#define PI 3.1415926
//const 定义常量, 只读变量
const int num = 101;

//字符串
//C系
//const char *str = "e";
//char str2[] = "hello";
//char str3[] = {'H','e','l','l','o','\0'};

//C++
//string str4 = "hello";
int main(){
    char a = '0';
    int b = 1;
    long c = 2;
    unsigned int d;//无符号整数变量
    float e;
    double f;
    return 0;
}