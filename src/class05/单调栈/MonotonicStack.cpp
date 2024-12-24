#include<bits/stdc++.h>
using namespace std;

// 定义常量N，表示数组的最大长度
const int N = 1e6 + 10;

// 定义全局数组
int arr[N];          // 存储输入的数组元素
int stack_arr[N];    // 模拟栈，用于存储数组索引
int r, n;            // r表示栈的当前大小，n表示数组长度
int ans[N][2];       // 存储每个位置的左右最近小于元素的位置
                     // ans[i][0]表示i位置左侧最近小于的索引
                     // ans[i][1]表示i位置右侧最近小于的索引

/**
 * @brief 使用单调栈计算每个位置左右最近小于的元素索引
 */
static void compute(){
    r = 0; // 初始化栈为空
    int cur; // 临时变量，存储当前弹出的索引

    // 遍历数组的每一个元素
    for(int i = 0; i < n; ++i){
        // 当栈不为空且当前元素小于或等于栈顶元素对应的值时，弹出栈顶元素
        while(r > 0 && arr[stack_arr[r-1]] >= arr[i]){
            cur = stack_arr[--r]; // 弹出栈顶元素的索引
            // 更新当前弹出元素的左侧最近小于的索引
            ans[cur][0] = (r > 0) ? stack_arr[r-1] : -1;
            // 更新当前弹出元素的右侧最近小于的索引为当前元素i
            ans[cur][1] = i;
        }
        // 将当前元素的索引压入栈
        stack_arr[r++] = i;
    }

    // 处理栈中剩余的元素，这些元素右侧没有更小的元素
    while(r > 0){
        cur = stack_arr[--r]; // 弹出栈顶元素的索引
        // 更新当前弹出元素的左侧最近小于的索引
        ans[cur][0] = (r > 0) ? stack_arr[r-1] : -1;
        // 右侧没有更小的元素，设为-1
        ans[cur][1] = -1;
    }

    // 修正阶段：处理数组中存在相同值的情况
    // 从右向左遍历，确保右侧最近小于的索引指向的是严格小于的元素
    for(int i = n - 2; i >= 0; --i){
        // 如果当前元素的右侧最近小于的位置存在且值与当前元素相同
        if(ans[i][1] != -1 && arr[i] == arr[ans[i][1]]){
            // 将右侧最近小于的位置更新为该位置的右侧最近小于的位置
            ans[i][1] = ans[ans[i][1]][1];
        }
    }
}

int main(){
    // 读取数组长度n
    scanf("%d", &n);
    
    // 读取数组的n个元素
    for(int i = 0; i < n; ++i){
        scanf("%d", arr + i);
    }

    // 调用compute函数计算每个位置的左右最近小于的元素索引
    compute();

    // 输出每个位置的左右最近小于的元素索引
    for(int i = 0; i < n; ++i){
        printf("%d %d\n", ans[i][0], ans[i][1]);
    }

    return 0; // 程序结束
}
