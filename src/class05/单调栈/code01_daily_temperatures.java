//提交内部类，并删除static即可
import java.util.Arrays;


// 每日温度
// 给定一个整数数组 temperatures ，表示每天的温度，返回一个数组 answer
// 其中 answer[i] 是指对于第 i 天，下一个更高温度出现在几天后
// 如果气温在这之后都不会升高，请在该位置用 0 来代替。
// 测试链接 : https://leetcode.cn/problems/daily-temperatures/
public class code01_daily_temperatures {
    static class Solution {
    private static int MAX = 100001;
    public static int[] stack = new int[MAX];
    public static int[] ans = new int[MAX];
    public static int r;
    public int[] dailyTemperatures(int[] temperatures) {
        int n = temperatures.length;
        r = 0;
        for(int i=0;i<n;i++){
            while(r > 0 && temperatures[stack[r-1]] < temperatures[i]){
                int pos = stack[--r];
                ans[pos] = i - pos;
            }
            stack[r++] = i;
        }
        while(r>0){
            ans[stack[--r]]=0;
        }
        return Arrays.copyOfRange(ans, 0, n);
    }
}
}
