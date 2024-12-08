### 自述
笔者最初接触的编程语言是C语言， 后面由于为了就业考虑学习Java, 当时试着与C++并行学习， 但后面

### C++语言


### STL使用


#### 顺序容器
`array`:升级版的静态数组\
`vector`：动态数组\
`deque`：双端队列\
`list`:双向链表\
`forward_list`:单向链表

#### 关联容器
`set`\
`map`\
`multiset`\
`multimap`

#### 无序容器
`unordered_set`\
`unordered_map`\
`unordered_multiset`\
`unordered_multimap`

#### 容器适配器
`stack`:栈\
`queue`:队列\
`priority_queue`：优先队列

#### 字符串
`string`:可变字符串序列

### 数组

适用静态数组建图\
链式前向星建图\
邻接矩阵建图

### 向量
`#include<vector.h>`

- 创建一个一维数组
`vector<int> arr;` 

- 初始化长度
`vector<int> arr(100)`

- 初始化长100的int数组， 初值为1
`vector<int> arr(100,-1)`


动态建图\
vector进行邻接表建图
普通数组卡常数时间， 替换为vector



### 栈
`#include<stack>`
实现方式， 二次封装deque容器， 实现了先进后出的栈。

- 创建一个栈`stack<int> stk;`
- 压栈`stk.push(1)`
- 查看栈顶元素`stk.top()`
- 出栈`stk.pop()`

