#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// 最大的石子数
const int MAXN = 1001;

// 动态规划表
vector<vector<string>> dp(MAXN, vector<string>(MAXN, ""));

// 方法1：动态规划进行所有尝试
string bashGame1(int n, int m) {
    if (n == 0) {
        return "后手";
    }
    if (!dp[n][m].empty()) {
        return dp[n][m];
    }
    string ans = "后手";
    for (int pick = 1; pick <= m; pick++) {
        if (bashGame1(n - pick, m) == "后手") {
            // 后续过程的赢家是后续过程的后手
            // 那就表示此时的先手，通过这个后续过程，能赢
            ans = "先手";
            break;
        }
    }
    dp[n][m] = ans;
    return ans;
}

// 方法2：正式方法（基于数学推导）
string bashGame2(int n, int m) {
    return n % (m + 1) != 0 ? "先手" : "后手";
}

int main() {
    srand(time(0)); // 随机种子
    int V = 500; // 需要比MAXN小
    int testTimes = 5000;
    
    cout << "测试开始" << endl;
    
    for (int i = 0; i < testTimes; i++) {
        int n = rand() % V;
        int m = rand() % V + 1;
        string ans1 = bashGame1(n, m);
        string ans2 = bashGame2(n, m);
        if (ans1 != ans2) {
            cout << "出错了!" << endl;
        }
    }
    
    cout << "测试结束" << endl;
    
    return 0;
}
