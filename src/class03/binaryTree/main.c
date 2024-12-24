#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXN 101
#define MAXM 6001

int head[MAXN], next[MAXM], to[MAXM], weight[MAXM], cnt = 1;
int dist[MAXN];
int visited[MAXN];

// 建立邻接表
void build(int n) {
    cnt = 1;
    for (int i = 0; i <= n; i++) {
        head[i] = -1;
    }
}

// 添加边到邻接表
void addEdge(int u, int v, int w) {
    next[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

// 实现最小堆
void heapify(int heap[][2], int size) {
    int i = 0;
    while (i * 2 + 1 < size) {
        int left = i * 2 + 1;
        int right = left + 1;
        int smallest = i;
        
        if (left < size && heap[left][1] < heap[smallest][1]) {
            smallest = left;
        }
        if (right < size && heap[right][1] < heap[smallest][1]) {
            smallest = right;
        }
        if (smallest == i) {
            break;
        }
        
        int temp[2] = {heap[i][0], heap[i][1]};
        heap[i][0] = heap[smallest][0];
        heap[i][1] = heap[smallest][1];
        heap[smallest][0] = temp[0];
        heap[smallest][1] = temp[1];
        i = smallest;
    }
}

int networkDelayTime(int times[][3], int timesSize, int n, int s) {
    build(n);

    // 建立图
    for (int i = 0; i < timesSize; i++) {
        addEdge(times[i][0], times[i][1], times[i][2]);
    }

    // 初始化距离数组
    for (int i = 1; i <= n; i++) {
        dist[i] = INT_MAX;
    }
    dist[s] = 0;

    // 初始化最小堆
    int heap[MAXN][2];
    int heapSize = 0;
    heap[heapSize][0] = s;
    heap[heapSize][1] = 0;
    heapSize++;

    // Dijkstra算法
    while (heapSize > 0) {
        // 弹出堆顶元素
        int u = heap[0][0];
        int d = heap[0][1];

        // 删除堆顶元素，调整堆
        heap[0][0] = heap[heapSize - 1][0];
        heap[0][1] = heap[heapSize - 1][1];
        heapSize--;
        heapify(heap, heapSize);

        if (visited[u]) {
            continue;
        }
        visited[u] = 1;

        // 更新邻接节点
        for (int ei = head[u]; ei != -1; ei = next[ei]) {
            int v = to[ei];
            int w = weight[ei];
            if (!visited[v] && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;

                // 将新的距离加入堆中
                heap[heapSize][0] = v;
                heap[heapSize][1] = dist[v];
                heapSize++;

                // 保证堆有序
                int i = heapSize - 1;
                while (i > 0 && heap[(i - 1) / 2][1] > heap[i][1]) {
                    int temp[2] = {heap[i][0], heap[i][1]};
                    heap[i][0] = heap[(i - 1) / 2][0];
                    heap[i][1] = heap[(i - 1) / 2][1];
                    heap[(i - 1) / 2][0] = temp[0];
                    heap[(i - 1) / 2][1] = temp[1];
                    i = (i - 1) / 2;
                }
            }
        }
    }

    // 找到最大延迟
    int ans = INT_MIN;
    for (int i = 1; i <= n; i++) {
        if (dist[i] == INT_MAX) {
            return -1;
        }
        ans = (ans > dist[i]) ? ans : dist[i];
    }

    return ans;
}

int main() {
    int times[][3] = {{2,1,1},{2,3,1},{3,4,1}};
    int timesSize = 3;
    int n = 4;
    int s = 2;
    int result = networkDelayTime(times, timesSize, n, s);
    printf("Network Delay Time: %d\n", result);
    return 0;
}
