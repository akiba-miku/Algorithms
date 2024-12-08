### 前置知识和本篇介绍
Kruskal算法需要借助以下两种数据结构。请读者朋友务必掌握后再阅读此篇。
**前置知识： `数据结构:优先级队列[可以用排序替代]`- `数据结构:并查集`**
编程语言:`Java/C++.`

不是所有图算法都要依赖建图，Kruskal算法是典型的不建图就可以用的图算法之一。

本篇介绍---最小生成树的概念以及Kruskal算法（读作克鲁斯卡尔算法， 一般可以用K算法代称）。 另外最小生成树算法还有一个Prim算法（普林算法）， 这一篇我发到另一篇文章`[探究经典Prim算法写法](https://blog.csdn.net/2303_79972050/article/details/144041234?spm=1001.2014.3001.5501)`
### 《最小生成树算法详解：Kruskal的优雅实现》

---
#### **一. 引言**
   - 什么是最小生成树（MST）？
   - 简要介绍 Kruskal 算法的核心思想和优势。

一家通信公司试图建立其各个计算机中心的通信联系。
它可以通过租用电话线连接任意之间的一对， 但不过这样成本太高了。 
能保证计算机中心能两两之间有通路即可吗？
比如这样以下的一个无向图， 如何保证其连通呢？ 
离散数学告诉我们， 简单连通无向图保证连通性是一棵树， 树状结构就可以保证连通性， 这棵树叫做生成树。
而这个图还带有权值， 由此衍生处一个最小生成树的概念。即生成树各边的权值之和最小的生成树。

以下是来自wiki的图，顶点表示计算机中心， 顶点之间用边表示， 其中边带有属性的权值就是费用。
从一个图中抽掉那些高昂的费用但不破坏图的连通性。
由于我们只需要保证连通和最低费用就可以了。 任意两个顶点之间只需要一条边连接就足够了。（生成树）
那么，按照上述删除连通无向图中的边的最终结构会形成一棵树（如下图黑色的边形成的树）。
`这棵树就是最小生成树。`
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/5cbf1ccdcb1a4f11bec83e790f0d1994.png)


最小生成树的两种算法都是基于贪心的策略， 即寻找局部最优解。
Kruskal算法是一种贪心算法， 它从边的角度出发， 用于`带权无向图`在寻找最小生成树。
下面讲述最小生成树的性质和算法流程。

#### **2. 最小生成树的性质**
   - 什么图具有最小生成树：
     - 1. 满足`无向`,`带权`,`连通`这些特征的图具有最小生成树。
     - 2. 生成树对于无向连通图的概念， 最小生成树要针对带权图， 否则就无`"最小"`的概念。
     - 3. **生成树存在是最小生成树存在的必要条件**， 对于无向带权图来说，只要存在一棵生成树， 那么最小生成树就是它本身； 如果存在多棵生成树， 那么最小生成树就是生成树权值比较最小的结果。
   - 最小生成树的定义：
     - 连通图中所有的顶点并且边权重之和最小的树结构。
   - 相关性质：
     - 最小生成树本质是树结构， 它满足树的性质
     - 生成树的边数为 $n-1$,`n`是无向连通图的顶点个数。
     - 不会成环。
     - 如何判断最小生成树是否存在？ 道理很简单，dfs或者bfs判断连通性即可， 或者可以统计边数是否满足`n-1`(下面的代码也是通过这种方式证明最小生成树不存在的)。
- 最小生成树不唯一：
	最小生成树的权值要求最小，但边的组织可能不同， 因此结构并不唯一。 存在多种最小生成树结构（最小权重和是相同的）。
#### **3. Kruskal 算法详解**
   - **3.1 Kruskal 的核心思想**
     - 每次选择最小的边， 将边添加进最小生成树结构里。期间可能存在成环情况（**这里借助并查集判环， 具体细节看代码部分**）， 直到添加`n-1条边`结束。
   - **3.2 算法流程**
     - 1. 若题目中给了图或者可以选择一种建图方式自己建好图， 遍历图中所有的边将它们排好序； 或者，收集好边的信息（两个端点， 权重）
     - 2. 按边权值升序排序。
     - 3. 使用并查集判断边是否形成环。（具体逻辑是判断两个端点是否在同一集合， 若存在则端点已经添加进最小生成树了必须舍弃该边; 否则加入最小生成树，并两个端点合并到一个集合）
     - 4. 逐步加入边，直到添加到n-1条边为止。
- **3.3 为什么正确性**
	基于贪心的策略， 每次选择权值最小的边且这条边不会成环或破坏连通性。 局部最优 == 全局最优。严格证明不必纠结。
    如果读者纠结证明可以阅读相关帖子， 算法导论， 或者直接读原作者的论文。

#### **4. Kruskal 算法的实现**
   - **4.1 数据结构选择**
     - 使用并查集（Union-Find）O(1)的时间进行合并， 高效地检测环。
     - 前面可以通过排序数组， 可以选择优先级队列或者更多广泛的堆结构（可合并堆）。
   - **4.2 实现细节**
     - 对边信息的处理
     - 并查集实现:路径压缩,按秩优化（我这里代码并未实现）
   - **4.3 Java代码实现**
[Kruskal模板题](https://www.luogu.com.cn/problem/P3366)
```java
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.io.StreamTokenizer;
import java.util.Arrays;
public class Main{
    //最大数据量
    public static int MAXN = 5001;
    public static int MAXM = 200001;
    
    //并查集模板数组
    public static int[] father = new int[MAXN];
    
    //边信息的处理
    public static int[][] edges = new int[MAXM][3];
    
    public static int n, m;
    
    //初始化并查集
    public static void build(int n){
        for(int i=1;i<=n;i++){
            father[i] = i;
        }
    }
    //向上找标记节点，并完成路径压缩
    public static int find(int i){
        if(i != father[i]){
            father[i] = find(father[i]);
        }
        return father[i];
    }
    //x，y不属于同一个集合就合并返回true
    //否则返回false.
    public static boolean union(int x,int y){
        int fx = find(x);
        int fy = find(y);
        if(fx == fy){
            return false;
        }else{
            father[fx] = fy;
            return true;
        }
    }
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StreamTokenizer in = new StreamTokenizer(br);
        PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
        while(in.nextToken() != StreamTokenizer.TT_EOF){
            n = (int)in.nval;
            in.nextToken();
            m = (int)in.nval;
            build(n);
            for(int i=1;i<=m;i++){
                in.nextToken();
                edges[i][0] = (int)in.nval;
                in.nextToken();
                edges[i][1] = (int)in.nval;
                in.nextToken();
                edges[i][2] = (int)in.nval;
            }
            //Kruskal依赖边权值的有序性
            //比较器快排一下。
            Arrays.sort(edges,1,m+1,(a,b) -> a[2] - b[2]);
            int ans = 0;
            int count = 0;
            //遍历所有边
            for(int[] edge : edges){
                //边的两个顶点不在并查集里， 合并两个并查集
                //将边添加进最小生成树中。
                if(union(edge[0], edge[1])){
                    count++;
                    ans += edge[2];
                }
            }
            out.println(count == n-1 ? ans : "orz");
        }
        out.flush();
        out.close();
        br.close();
    }
}
```

`C++代码实现`
```cpp
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
```

#### **5. Kruskal 算法的时间复杂度分析**
时间复杂度:$O(mlogm + n + m)$
收集边的信息，对边按权值排序， 遍历边生成最小生成树。
并查集操作$O(1)$

#### **6. Kruskal 算法的优缺点**
   - 优点：
     - 适合稀疏图（边数较少）。
     - 算法逻辑清晰易懂。
   - 缺点：
     - 需要对边排序，复杂度较高。
     - 不适合边权值频繁动态更新的情况。

### 结语
Java/C++简单明了的逻辑和优雅的实现方式。在某些特殊情况下，算法的效率可能受到边排序和并查集操作的影响，但由于不用建图，且非常好写， K算法非常受欢迎。
笔者才疏学浅， 对于图论算法仅仅只有点到为止的理解。希望通过这篇文章，我的拙见能帮助您能对Kruskal算法有更深入的了解，并能够根据实际问题选择合适的算法。
无论是在面对稀疏图时的高效表现，还是在理解最小生成树的过程中，Kruskal都为我们提供了一个宝贵的思路和工具。

对于有另一个生成树算法Prim感兴趣的读者，别忘了查看相关的Prim算法讨论，它是另一个重要的最小生成树算法，虽然实现方式与Kruskal有所不同，但同样发挥着重要作用。

祝你在算法学习之路上越走越远！


~~前面一篇写得太烂了，  偷偷删除,同时补充C++代码重新发一遍...~~

