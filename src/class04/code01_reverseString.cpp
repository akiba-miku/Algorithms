//leetcode：https://leetcode.cn/problems/reverse-string/
#include<bits/stdc++.h>
class Solution {
public:
    void reverseString(std::vector<char>& s) {
        int l=0,r=s.size()-1;
        while(l<r){
          std::swap(s[l],s[r]);
          l++,r--;
        }
        //调用算法库的reverse也是可以的
        // std::reverse(s.begin(),s.end());
    }
};