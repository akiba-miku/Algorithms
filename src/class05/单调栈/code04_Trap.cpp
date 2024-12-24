#include<bits/stdc++.h>
using namespace std;

//接雨水：
//难度：Hard
//给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，
//计算按此排列的柱子，下雨之后能接多少雨水。
//测试链接:https://leetcode.cn/problems/trapping-rain-water/
//提供一个示例：

const int N = 2e5 + 10;  // 定义一个较大的常数N，确保栈数组足够大
int stack_arr[N];         // 栈数组，用于保存柱子的索引
int r;                    // 栈的大小（栈顶指针），表示栈中元素的个数

class Solution {
public:
    int trap(vector<int>& height) {  // 主函数，输入为柱子的高度数组height
        r = 0;  // 初始化栈的大小为0
        int sum = 0;  // 用于存储总的接水量
        int dis;  // 存储左右边界之间的距离
        int n = height.size();  // 获取柱子高度数组的长度

        for (int i = 0; i < n; ++i) {  // 遍历每一个柱子
            // 当栈非空且当前柱子的高度大于栈顶柱子的高度时，计算水量
            while (r > 0 && height[stack_arr[r - 1]] <= height[i]) {
                int pos = stack_arr[--r];  // 弹出栈顶元素，即当前柱子的下标
                if (r > 0) {  // 确保栈中还有元素
                    dis = i - stack_arr[r - 1] - 1;  // 计算左边界和右边界之间的距离
                    int bounded_height = min(height[stack_arr[r - 1]], height[i]) - height[pos];  // 计算有效的水面高度
                    sum += dis * bounded_height;  // 将接到的水量加到总水量中
                }
            }
            stack_arr[r++] = i;  // 将当前柱子的下标压入栈中
        }

        return sum;  // 返回总的接水量
    }
};
