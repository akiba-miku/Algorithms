#include<bits/stdc++.h>
using namespace std;
// 子数组的最小值之和
// 给定一个整数数组 arr，找到 min(b) 的总和，其中 b 的范围为 arr 的每个（连续）子数组。
// 由于答案可能很大，答案对 1000000007 取模
// 测试链接 : https://leetcode.cn/problems/sum-of-subarray-minimums/

//乘法同余原理.
#define ll long long
const int mod = 1e9+7, N = 3e4+10;
int stack_arr[N];
int r;
class Solution {
public:
    int sumSubarrayMins(vector<int>& arr) {
        int n = arr.size();
        r = 0;
        ll ans = 0;
        //单调递增栈
        for(int i=0;i<n;i++){
            while(r>0&&arr[stack_arr[r-1]]>=arr[i]){
                int cur = stack_arr[--r];
                int l = r>0?stack_arr[r-1]:-1;
                ans = (ans + (ll)(cur-l)*(i-cur)*arr[cur])%mod;
            }
            stack_arr[r++]=i;
        }
        while(r>0){
            int cur = stack_arr[--r];
            int l = r>0?stack_arr[r-1]:-1;
            ans = (ans+(ll)(cur-l)*(n-cur)*arr[cur])%mod;
        }
        return (int)ans;
    }
};