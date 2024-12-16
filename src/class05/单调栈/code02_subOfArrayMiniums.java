// 子数组的最小值之和
// 给定一个整数数组 arr，找到 min(b) 的总和，其中 b 的范围为 arr 的每个（连续）子数组。
// 由于答案可能很大，答案对 1000000007 取模
// 测试链接 : https://leetcode.cn/problems/sum-of-subarray-minimums/

//乘法同余原理.

public class code02_subOfArrayMiniums {
    static class Solution {
        public static int mod = (int)1e9+7, N = (int)3e4+10;
        public static int[] stack = new int[N];
        static int r;
        public int sumSubarrayMins(int[] arr) {
            r = 0;
            long ans = 0;
            for(int i=0;i<arr.length;i++){
                while(r>0&&arr[stack[r-1]]>=arr[i]){
                    int pos = stack[--r];
                    int l = r>0?stack[r-1]:-1;
                    ans = (ans + (long)(i-pos)*(pos-l)*arr[pos])%mod;
                }
                stack[r++] = i;
            }
            while(r>0){
                int cur = stack[--r];
                int l = r>0?stack[r-1]:-1;
                ans = (ans + (long)(cur-l)*(arr.length-cur)*arr[cur])%mod;
            }
            return (int)ans;
        }
    }
}
