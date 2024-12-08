// #include <iostream>
// #include <vector>
// #include <queue>
// #include <climits>
// #include <cstring>
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 5001;
const int MAXM = 400001;

int head[MAXN], next_edge[MAXM], to[MAXM], weight[MAXM];
int cnt = 1;

void build(int n) {
    cnt = 1;
    memset(head, 0, sizeof(int) * (n + 1));
}

void add_edge(int u, int v, int w) {
    next_edge[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}



int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    while (cin >> n) {
        build(n);

        cin >> m;

        // Reading all edges
        for (int i = 0; i < m; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            add_edge(u,v,w);
            add_edge(v,u,w);
        }

        // If there is only one node, MST weight is 0
        if (n == 1) {
            cout << 0 << endl;
            continue;
        }

        // Priority queue to store the edges sorted by weight
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        // Add all edges of node 1 to the priority queue
        for (int ei = head[1]; ei != 0; ei = next_edge[ei]) {
            pq.push({weight[ei], to[ei]});
        }

        vector<bool> set(n + 1, false);  // To track which nodes are included in MST
        int verticesCnt = 1;  // Number of nodes included in the MST
        int ans = 0;  // The total weight of the MST

        set[1] = true;  // Include node 1 in the MST

        while (!pq.empty()) {
            auto edge = pq.top();
            pq.pop();
            int cost = edge.first;
            int toNode = edge.second;

            if (!set[toNode]) {
                set[toNode] = true;
                verticesCnt++;
                ans += cost;

                // Add all edges from the new node to the priority queue
                for (int ej = head[toNode]; ej != 0; ej = next_edge[ej]) {
                    pq.push({weight[ej], to[ej]});
                }
            }
        }

        // If all nodes are included in the MST, print the total weight, otherwise print "orz"
        if (verticesCnt == n) {
            cout << ans << endl;
        } else {
            cout << "orz" << endl;
        }
    }

    return 0;
}
