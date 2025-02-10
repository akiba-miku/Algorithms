// 测试链接 : https://www.luogu.com.cn/problem/P1048
#include <bits/stdc++.h>
using namespace std;

const int N = 1001;
int costs[N], values[N];
int t, m;
int dp[N][N]; // 二维dp表

void compute() {
    // 初始化dp数组， 全局初始化默认为0，这里不必显式初始化。
    // for (int i = 0; i <= t; i++) {
    //     dp[0][i] = 0; // 如果没有物品，背包的最大值肯定是0
    // }

    // 遍历所有物品
    for (int i = 1; i <= m; i++) {
        // 遍历所有背包容量
        for (int j = 0; j <= t; j++) {
            // 不选择第i个物品
            dp[i][j] = dp[i - 1][j];
            // 选择第i个物品（如果容量允许）
            if (j >= costs[i]) {
                dp[i][j] = max(dp[i][j], dp[i - 1][j - costs[i]] + values[i]);
            }
        }
    }
}

int main() {
    scanf("%d%d", &t, &m); // 输入背包容量t和物品个数m
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &costs[i], &values[i]); // 输入每个物品的重量（costs）和价值（values）
    }
    
    compute(); // 计算最大价值
    
    printf("%d\n", dp[m][t]); // 输出最终结果：最大价值
    return 0;
}