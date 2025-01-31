#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

class BigInt {
private:
    // 用数组存储大数，每个元素表示数字的一部分
    vector<int> digits; // 存储每个数字位上的值，低位在前
    bool isNegative; // 标记是否为负数

public:
    // 默认构造函数，构造 0
    BigInt() {
        isNegative = false;
        digits.push_back(0);  // 默认数字 0
    }

    // 从字符串构造大整数
    BigInt(const string& num) {
        isNegative = (num[0] == '-');
        for (int i = num.size() - 1; i >= (isNegative ? 1 : 0); --i) {
            digits.push_back(num[i] - '0');
        }
    }

    // 打印大整数
    void print() const {
        if (isNegative && !(digits.size() == 1 && digits[0] == 0)) {
            cout << "-";
        }
        for (int i = digits.size() - 1; i >= 0; --i) {
            cout << digits[i];
        }
        cout << endl;
    }

    // 大整数加法
    BigInt operator+(const BigInt& other) const {
        if (isNegative == other.isNegative) {
            BigInt result;
            result.isNegative = isNegative;
            int carry = 0;
            int maxLength = max(digits.size(), other.digits.size());
            result.digits.resize(maxLength);

            for (int i = 0; i < maxLength || carry; ++i) {
                int sum = carry;
                if (i < digits.size()) sum += digits[i];
                if (i < other.digits.size()) sum += other.digits[i];
                result.digits[i] = sum % 10;
                carry = sum / 10;
            }
            return result;
        } else if (isNegative) {
            // 负数加法转为减法
            BigInt temp = *this;
            temp.isNegative = false;
            return other - temp;
        } else {
            // 正数加法转为负数减法
            BigInt temp = other;
            temp.isNegative = false;
            return *this - temp;
        }
    }

    // 大整数减法
    BigInt operator-(const BigInt& other) const {
        if (isNegative != other.isNegative) {
            // 负数减去正数 转为加法
            BigInt temp = other;
            temp.isNegative = !temp.isNegative;
            return *this + temp;
        } else if (isNegative) {
            // 负数减负数 转为减法
            BigInt temp = *this;
            temp.isNegative = false;
            return other - temp;
        } else {
            // 正数减法
            if (*this < other) {
                BigInt result = other - *this;
                result.isNegative = true;
                return result;
            }
            BigInt result;
            result.digits.resize(digits.size());
            int borrow = 0;
            for (int i = 0; i < digits.size(); ++i) {
                int diff = digits[i] - borrow;
                if (i < other.digits.size()) {
                    diff -= other.digits[i];
                }
                if (diff < 0) {
                    diff += 10;
                    borrow = 1;
                } else {
                    borrow = 0;
                }
                result.digits[i] = diff;
            }

            // 清除高位的零
            while (result.digits.size() > 1 && result.digits.back() == 0) {
                result.digits.pop_back();
            }
            return result;
        }
    }

    // 大整数乘法
    BigInt operator*(const BigInt& other) const {
        BigInt result;
        result.digits.resize(digits.size() + other.digits.size(), 0);
        for (int i = 0; i < digits.size(); ++i) {
            for (int j = 0; j < other.digits.size(); ++j) {
                result.digits[i + j] += digits[i] * other.digits[j];
                if (result.digits[i + j] >= 10) {
                    result.digits[i + j + 1] += result.digits[i + j] / 10;
                    result.digits[i + j] %= 10;
                }
            }
        }
        
        // 清除高位的零
        while (result.digits.size() > 1 && result.digits.back() == 0) {
            result.digits.pop_back();
        }

        result.isNegative = (isNegative != other.isNegative);
        return result;
    }

    // 比较大小
    bool operator<(const BigInt& other) const {
        if (isNegative != other.isNegative) {
            return isNegative;
        }

        if (digits.size() != other.digits.size()) {
            return (digits.size() < other.digits.size()) ^ isNegative;
        }

        for (int i = digits.size() - 1; i >= 0; --i) {
            if (digits[i] != other.digits[i]) {
                return (digits[i] < other.digits[i]) ^ isNegative;
            }
        }

        return false;
    }

    // 比较是否相等
    bool operator==(const BigInt& other) const {
        return digits == other.digits && isNegative == other.isNegative;
    }

    // 比较是否不相等
    bool operator!=(const BigInt& other) const {
        return !(*this == other);
    }

    // 除法可以通过其他算法实现，但由于篇幅较长，这里仅提供加法、减法和乘法。
};

// 主函数示例
int main() {
    BigInt a("123456789123456789123456789");
    BigInt b("987654321987654321987654321");

    BigInt sum = a + b;
    BigInt diff = a - b;
    BigInt prod = a * b;

    cout << "a + b = ";
    sum.print();
    cout << "a - b = ";
    diff.print();
    cout << "a * b = ";
    prod.print();

    return 0;
}
