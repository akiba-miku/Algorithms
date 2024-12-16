//接雨水：
//难度:Hard
//给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，
//计算按此排列的柱子，下雨之后能接多少雨水。
//测试链接:https://leetcode.cn/problems/trapping-rain-water/

//提交内部类，并删除static
public class code04_Trap {
    static class Solution {
        //单调栈解法
        public static int N = (int) 2e5 + 1;
        public static int[] stack = new int[N];
        public static int r;
    
        public static int trap(int[] height) {
            r = 0; // stack的当前索引
            int sum = 0; // 最终接水量
            for (int i = 0; i < height.length; i++) {
                // 如果当前柱子比栈顶的柱子高，弹出栈顶元素计算接水量
                while (r > 0 && height[stack[r - 1]] < height[i]) {
                    int pos = stack[--r]; // 弹出栈顶元素
                    if (r > 0) {
                        // 计算接水量
                        int dis = i - stack[r - 1] - 1; // 计算宽度
                        int h = Math.min(height[stack[r - 1]], height[i]) - height[pos]; // 计算水的高度
                        sum += dis * h; // 计算当前区域的水量并累加
                    }
                }
                stack[r++] = i; // 将当前柱子的索引入栈
            }
            return sum;
        }
    
        // 双指针最优解
        public static int trap1(int[] height) {
            if (height == null || height.length < 2) {
                return 0;
            }
            int l = 1, r = height.length - 2; // 双指针，分别指向左右两边
            int lmax = height[0], rmax = height[height.length - 1]; // 左右两侧的最大高度
            int ans = 0;
            for (; l <= r;) {
                if (lmax > rmax) {
                    // 右边界更新
                    ans += Math.max(0, rmax - height[r]);
                    rmax = Math.max(rmax, height[r--]);
                } else {
                    // 左边界更新
                    ans += Math.max(0, lmax - height[l]);
                    lmax = Math.max(lmax, height[l++]);
                }
            }
            return ans;
        }
    
    }
}
