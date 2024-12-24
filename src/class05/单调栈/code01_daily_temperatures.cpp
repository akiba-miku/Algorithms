#include<bits/stdc++.h>
using namespace std;
//提交时注释这段

///
// 每日温度
// 给定一个整数数组 temperatures ，表示每天的温度，返回一个数组 answer
// 其中 answer[i] 是指对于第 i 天，下一个更高温度出现在几天后
// 如果气温在这之后都不会升高，请在该位置用 0 来代替。
// 测试链接 : https://leetcode.cn/problems/daily-temperatures/
const int N = 1e5+1;
int stack_arr[N];
int r;
int ans[N];
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& t) {
        r=0;
        int n = t.size(), cur;
        for(int i=0;i<n;++i){
            while(r>0&&t[stack_arr[r-1]]<t[i]){
                cur = stack_arr[--r];
                ans[cur]=i-cur;
            }
            stack_arr[r++]=i;
        }
        while(r>0){
            ans[stack_arr[--r]]=0;
        }
        return vector<int> (ans,ans+n);
    }
};