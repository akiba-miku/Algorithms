// 柱状图中最大的矩形
// 给定 n 个非负整数，用来表示柱状图中各个柱子的高度
// 每个柱子彼此相邻，且宽度为 1 。求在该柱状图中，能够勾勒出来的矩形的最大面积
// 测试链接：https://leetcode.cn/problems/largest-rectangle-in-histogram

#include<bits/stdc++.h>>
using namespace std;
const int N = 1e5+10;
int stack_arr[N];
int r;
class Solution {
public:
    int largestRectangleArea(vector<int>& h) {
        r = 0;
        int n = h.size();
        int ans = 0;
        for(int i=0;i<n;++i){
            while(r>0&&h[stack_arr[r-1]]>=h[i]){
                int pos = stack_arr[--r];
                int l = r>0?stack_arr[r-1]:-1;
                ans = max(ans, (i-l-1)*h[pos]);
            }
            stack_arr[r++]=i;
        }
        while(r>0){
            int pos = stack_arr[--r];
            int l = r>0?stack_arr[r-1]:-1;
            ans = max(ans, (n-l-1)*h[pos]);
        }
        return ans;
    }
};