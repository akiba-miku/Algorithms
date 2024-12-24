// 柱状图中最大的矩形
// 给定 n 个非负整数，用来表示柱状图中各个柱子的高度
// 每个柱子彼此相邻，且宽度为 1 。求在该柱状图中，能够勾勒出来的矩形的最大面积
// 测试链接：https://leetcode.cn/problems/largest-rectangle-in-histogram

//提交内部类， 删除static关键字。
public class code03_LargestRectangleInHistogra {
    static class Solution {
        public static final int MAXN = (int)1e5+10;  
        public static int[] stack = new int[MAXN];
        public static int r;
        public int largestRectangleArea(int[] heights) {
            //单调递减栈
            r= 0;
            long ans = 0L;
            for(int i=0;i<heights.length;++i){
                while(r>0&&heights[stack[r-1]]>=heights[i]){
                    int pos = stack[--r];
                    int l = r>0?stack[r-1]:-1;
                    ans = Math.max(ans, (long)(i-l-1)*heights[pos]);
                }
                stack[r++] = i;
            }
            while(r>0){
                int pos = stack[--r];
                int l = r>0?stack[r-1]:-1;
                ans = Math.max(ans, (long)(heights.length-l-1)*heights[pos]);
            }
            return (int)ans;
        }
    }
}
