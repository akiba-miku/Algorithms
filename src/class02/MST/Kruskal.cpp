#include <bits/stdc++.h>
using namespace std;

#define MAXN 5001
#define MAXM 20001

int father[MAXN];
vector<array<int, 3>> edge;
int n, m;

// 初始化并设置父节点
static void build(int n) {
    for (int i = 1; i <= n; i++) {
        father[i] = i;
    }
}

// 查找父节点并进行路径压缩
static int find(int i) {
    if (i != father[i]) {
        father[i] = find(father[i]);  // 路径压缩
    }
    return father[i];
}

// 合并两个集合
static bool union_sets(int x, int y) {
    int fx = find(x), fy = find(y);
    if (fx != fy) {
        father[fx] = fy;  // 合并
        return true;
    }
    return false;
}

int main(void) {
    cin >> n >> m;

    build(n);

    edge.resize(m);
    
    // 输入边数据
    for (int i = 0; i < m; i++) {
        cin >> edge[i][0] >> edge[i][1] >> edge[i][2];
    }

    // 按照边权重升序排序（a[2] 是权重，b[2] 是权重）
    sort(edge.begin(), edge.end(), [](const array<int, 3>& a, const array<int, 3>& b) {
        return a[2] < b[2];  // 比较权重
    });

    int cnt = 0;  // 记录最小生成树的边数
    int ans = 0;  // 记录最小生成树的权重

    for (const auto& e : edge) {
        if (union_sets(e[0], e[1])) {
            cnt++;
            ans += e[2];
        }
    }

    // 判断是否生成了最小生成树
    if (cnt == n - 1) {
        printf("%d\n", ans);
    } else {
        printf("orz\n");
    }

    return 0;
}

