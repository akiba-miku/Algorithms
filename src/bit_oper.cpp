#include<bits/stdc++.h>
using namespace std;

//提取符号位
int sign(int x){
    return ~((x>>31)&1);
}
//x要么是0,要么是1
int flip(int x){
    return x ^ 1;
}
//不使用比较操作决出最大值。
int get_max_of_two(int a,int b){
    int c = a - b;
    int a_max = sign(c);
    int b_max = flip(a_max);
    //c>0选择a， c<0选择b, c=0实际选择a，但ab相同无所谓。
    return a_max * a + b_max * b;
}
int main(void){
    int a,b;
    cin>>a>>b;
    printf("a与b两数最大值是:%d\n", get_max_of_two(a,b));
    return 0;
}





















// void swap_array(int *a,int i,int j){
//     a[i] ^= a[j];
//     a[j] ^= a[i];
//     a[i] ^= a[j];
// }
// int main(void){
//     int a[1];
//     a[0] = 10;
//     printf("跟自己交换前->a[0]:%d\n",a[0]);
//     swap_array(a,0,0);
//     printf("跟自己交换后->a[0]:%d\n",a[0]);
//     return 0;
// }









// void swap_c(int *a,int *b){
//     *a ^= *b;
//     *b ^= *a;
//     *a ^= *b;
// }
// int main(){
//     //交换两个数
//     int a = 10;
//     int b = 20;
//     //std标准库内置了swap函数
//     //swap(a,b);
//     printf("a:%d b:%d\n",a,b);
//     //可以尝试调swap_c函数来交换
//     swap_c(&a,&b);
//     // a = a ^ b;
//     // b = a ^ b;
//     // a = a ^ b;
//     printf("a:%d b:%d\n",a,b);
// }