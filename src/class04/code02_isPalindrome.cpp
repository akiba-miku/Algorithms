//leetcode:https://leetcode.cn/problems/valid-palindrome/
#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool isPalindrome(string s) {
        int l=0,r=s.size()-1;
        while(l<r){
          //l往左找第一个数字或者字母字符
          while(l<r&&!isalnum(s[l])) ++l;
          //r从右往左找第一个数字或者字母字符
          while(l<r&&!isalnum(s[r])) --r;
          //如果是字母字符统一转大写比较。
          if(toupper(s[l])!=toupper(s[r])) return false;
          l++,--r;
        }
        return true;
    }
};