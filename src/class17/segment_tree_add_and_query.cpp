//线段树经典堆式结构实现.
//C++代码实现
//----------------
// 线段树支持范围增加、范围查询
// 维护累加和
// 测试链接 : https://www.luogu.com.cn/problem/P3372
//大致记忆类似归并排序的写法， 建树,范围查询，范围修改(懒更新/下发)

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 最大节点数
const int MAXN = 100001;

// 原始数组
ll arr[MAXN];

// 线段树的sum和add数组
ll sum_tree[MAXN << 2];
ll add_tree[MAXN << 2];

// 汇总累加和信息
void up(int i) {
    sum_tree[i] = sum_tree[i << 1] + sum_tree[i << 1 | 1];
}

// 懒信息下发
void down(int i, int ln, int rn) {
    if (add_tree[i] != 0) {
        // 下发给左孩子
        add_tree[i << 1] += add_tree[i];
        sum_tree[i << 1] += add_tree[i] * ln;
        // 下发给右孩子
        add_tree[i << 1 | 1] += add_tree[i];
        sum_tree[i << 1 | 1] += add_tree[i] * rn;
        // 清空当前节点的懒信息
        add_tree[i] = 0;
    }
}

// 懒更新
void lazy_update(int i, ll v, int n) {
    sum_tree[i] += v * n;
    add_tree[i] += v;
}

// 建树
void build(int l, int r, int i) {
    if (l == r) {
        sum_tree[i] = arr[l];
    } else {
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
        up(i);
    }
    add_tree[i] = 0;
}

// 范围修改：给[jobl, jobr]范围内每个元素增加jobv
void range_add(int jobl, int jobr, ll jobv, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        lazy_update(i, jobv, r - l + 1);
    } else {
        int mid = (l + r) >> 1;
        down(i, mid - l + 1, r - mid);
        if (jobl <= mid) {
            range_add(jobl, jobr, jobv, l, mid, i << 1);
        }
        if (jobr > mid) {
            range_add(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
        }
        up(i);
    }
}

// 查询范围[jobl, jobr]的累加和
ll range_query(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return sum_tree[i];
    }
    int mid = (l + r) >> 1;
    down(i, mid - l + 1, r - mid);
    ll ans = 0;
    if (jobl <= mid) {
        ans += range_query(jobl, jobr, l, mid, i << 1);
    }
    if (jobr > mid) {
        ans += range_query(jobl, jobr, mid + 1, r, i << 1 | 1);
    }
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= n; ++i){
        cin >> arr[i];
    }
    build(1, n, 1);
    for(int i = 0; i < m; ++i){
        int op;
        cin >> op;
        if(op == 1){
            int jobl, jobr;
            ll jobv;
            cin >> jobl >> jobr >> jobv;
            range_add(jobl, jobr, jobv, 1, n, 1);
        }
        else{
            int jobl, jobr;
            cin >> jobl >> jobr;
            cout << range_query(jobl, jobr, 1, n, 1) << "\n";
        }
    }
    return 0;
}
