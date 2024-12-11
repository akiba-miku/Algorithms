//https://www.luogu.com.cn/problem/P4715
#include<bits/stdc++.h>
using namespace std;

const int N = 256;
queue<pair<int, int>> qe; // 存储 pair 而非指针

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    int m = 1 << n; // 2^n
    for (int i = 1, x; i <= m; ++i) {
        cin >> x;
        qe.push({i, x}); // 存储值而非地址
    }

    pair<int, int> first, second;
    while (qe.size() != 2) {
        first = qe.front();
        qe.pop();
        second = qe.front();
        qe.pop();
        if (first.second > second.second) 
            qe.push(first);
        else 
            qe.push(second);
    }

    first = qe.front();
    qe.pop();
    second = qe.front();
    qe.pop();
    int res = first.second > second.second ? second.first : first.first;
    cout << res << '\n';
    return 0;
}
