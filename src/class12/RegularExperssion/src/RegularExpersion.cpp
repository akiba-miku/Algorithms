// 正则表达式匹配
// 给你字符串s、字符串p
// s中一定不含有'.'、'*'字符，p中可能含有'.'、'*'字符
// '.' 表示可以变成任意字符，数量1个
// '*' 表示可以让 '*' 前面那个字符数量任意(甚至可以是0个)
// p中即便有'*'，一定不会出现以'*'开头的情况，也一定不会出现多个'*'相邻的情况(无意义)
// 请实现一个支持 '.' 和 '*' 的正则表达式匹配
// 返回p的整个字符串能不能匹配出s的整个字符串
// 测试链接 : https://leetcode.cn/problems/regular-expression-matching/
// 通过率: 100%。 提交时可以删除头文件和main函数，只保留类及compute函数即可

//下面提供C++11标准正则表达式库与实际实现的对比测试
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <regex>  // 包含标准库中的正则表达式库

using namespace std;

bool compute(string s, string p) {
    int n = s.size();
    int m = p.size();
    vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, 0));
    dp[n][m] = 1;
    
    // p的后缀匹配处理
    for (int j = m - 2; j >= 0; j--) {
        if (p[j + 1] == '*') {
            dp[n][j] = dp[n][j + 2];
        }
    }
    
    // 动态规划填充dp表
    for (int i = n - 1; i >= 0; i--) {
        for (int j = m - 1; j >= 0; j--) {
            if (j + 1 == m || p[j + 1] != '*') {
                dp[i][j] = (s[i] == p[j] || p[j] == '.') && dp[i + 1][j + 1];
            } else {
                dp[i][j] = dp[i][j + 2] || (s[i] == p[j] || p[j] == '.') && dp[i + 1][j];
            }
        }
    }
    
    return dp[0][0];
}

class Solution {
public:
    bool isMatch(string s, string p) {
        return compute(s, p);
    }
};

// 使用C++标准库的正则表达式匹配
bool stdRegexMatch(string s, string p) {
    try {
        regex pattern(p);
        return regex_match(s, pattern);
    } catch (const regex_error& e) {
        cout << "Regex error: " << e.what() << endl;
        return false;
    }
}

// 随机生成字符串s
string generateString(int length) {
    string result = "";
    for (int i = 0; i < length; ++i) {
        result += (rand() % 26) + 'a'; // 生成小写字母
    }
    return result;
}

// 随机生成标准的正则表达式模式p
string generatePattern(int length) {
    string result = "";
    bool lastWasStar = true;  // 标记上一个字符是否是'*'
    
    for (int i = 0; i < length; ++i) {
        // 控制生成的模式规则
        if (rand() % 4 == 0 && !lastWasStar) {  // 约25%的概率选择 '*'，但不能连续生成
            result += '*';
            lastWasStar = true;  // 设置标记
        } else if (rand() % 4 == 1) {  // 约25%的概率选择 '.'
            result += '.';
            lastWasStar = false;
        } else {
            result += (rand() % 26) + 'a';  // 其他情况下选择字母
            lastWasStar = false;
        }
    }
    
    return result;
}

int main() {
    srand(time(0));  // 设置随机种子
    Solution sol;
    
    int testCases = 1000;//测试数据量
    cout << "测试开始" << endl;
    
    for (int i = 0; i < testCases; ++i) {
        int sLength = rand() % 20 + 1;  // s的长度为1到20之间
        int pLength = rand() % 20 + 1;  // p的长度为1到20之间
        
        string s = generateString(sLength);  // 生成随机字符串s
        string p = generatePattern(pLength); // 生成随机模式p
        
        // 调用自定义的正则表达式匹配函数并验证
        bool customResult = sol.isMatch(s, p);  // 自定义实现
        bool stdResult = stdRegexMatch(s, p);  // 使用std::regex实现
        
        // 输出测试用例并验证正确性
        if (customResult != stdResult) {
            cout << "测试失败!" << endl;
            cout << "s: " << s << ", p: " << p << endl;
            cout << "手写测试结果: " << customResult << ", 标准库结果: " << stdResult << endl;
            break;
        }
        
        // 每100次输出一次进度
        if (i % 100 == 0) {
            cout << "已完成 " << i << " 次测试" << endl;
        }
    }
    
    cout << "测试结束" << endl;
    return 0;
}