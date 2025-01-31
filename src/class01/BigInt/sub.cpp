#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using std::cin;
using std::cout;
using std::endl;

// 高精度减法
std::string sub(const std::string& a, const std::string& b){
    std::vector<int> A, B;
    
    // 将字符串 a 转换成数字数组 A（逆序存储）
    for (int i = a.size() - 1; i >= 0; i--) {
        A.push_back(a[i]-'0');
    }

    // 将字符串 b 转换成数字数组 B（逆序存储）
    for (int i = b.size() - 1; i >= 0; i--) {
        B.push_back(b[i]-'0');
    }

    // 比较 a 和 b 的大小，设置 isPos 为 true 表示 a >= b，否则为 false
    bool isPos = true; // 默认 a >= b
    if(A.size() != B.size()){
        isPos = A.size() > B.size();
    } else {
        // 长度相同，逐位比较
        bool found = false;
        for(int i = A.size()-1; i >= 0; i--){
            if(A[i] != B[i]){
                isPos = A[i] > B[i];
                found = true;
                break;
            }
        }
        if(!found){
            // a 和 b 完全相等
            return "0";
        }
    }

    std::string c;
    if(isPos){
        // 执行 a - b
        int t = 0;
        for(int i = 0; i < A.size(); i++){
            t=A[i]-t;
            if(i<B.size()) t-=B[i];
            c.push_back((t+10)%10+'0');
            t = t<0?1:0;
        }
    }
    else{
        // 执行 b - a
        int t = 0;
        for(int i = 0; i < B.size(); i++){
            t=B[i]-t;
            if(i<A.size()) t-=A[i];
            c.push_back((t+10)%10+'0');
            t = t<0?1:0;
        }
    }

    // 去除结果中的前导零
    while(c.size() > 1 && c.back() == '0') c.pop_back();
    //负数添加符号
    if(!isPos){
        c.push_back('-');
    }

    // 反转字符串， 输出就是高位到低位的顺序。
    std::reverse(c.begin(), c.end());

    return c;
}

int main() {
    std::string a, b;
    getline(cin, a);  // 输入第一个大整数
    getline(cin, b);  // 输入第二个大整数

    // 输出减法结果
    std::cout << sub(a, b) << std::endl;

    return 0;
}