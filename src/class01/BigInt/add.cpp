#include <iostream>
#include <vector>
#include <string>
#include<algorithm>
using std::cin;
using std::cout;
using std::endl;

// 高精度加法
std::string add(const std::string& a, const std::string& b) {
    std::vector<int> A, B;

    // 将字符串 a 转换成数字数组 A
    for (int i = a.size() - 1; i >= 0; i--) {
        A.push_back(a[i] - '0');
    }

    // 将字符串 b 转换成数字数组 B
    for (int i = b.size() - 1; i >= 0; i--) {
        B.push_back(b[i] - '0');
    }

    // 执行加法
    std::string c;
    int n1 = a.size(), n2 = b.size();
    int t = 0;  // 进位
    for (int i = 0; i < n1 || i < n2 || t; i++) {
        if (i < n1) t += A[i];  // 如果 A 中还有数字，加上该位
        if (i < n2) t += B[i];  // 如果 B 中还有数字，加上该位

        c.push_back(t % 10 + '0');  // 当前位数的结果
        t /= 10;  // 更新进位
    }

    // 结果字符串已经是逆序的，因此需要将其反转
    std::reverse(c.begin(), c.end());
    
    return c;
}

int main() {
    std::string a, b;
    getline(cin, a);  // 输入第一个大整数
    getline(cin, b);  // 输入第二个大整数

    // 输出加法结果
    cout << add(a, b) << endl;
    return 0;
}
