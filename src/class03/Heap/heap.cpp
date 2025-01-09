#include<bits/stdc++.h>
using namespace std;
const int N = 1e6+10;
int heap[N],hz;
void init(){
    hz = 0;
}

//上浮操作
void push_up(int i){
    while (heap[i]<heap[(i-1)/2]){
        swap(heap[i], heap[(i-1)/2]);
        i = (i-1)/2;
    }
}

//下沉操作
void push_down(int i){
    int l=i*2+1;//l是左孩子
    while(l<hz){
        //找出最棒的孩子，优先级最高的孩子
        int best = l+1<hz&&heap[l+1]<heap[l]?l+1:l;
        best = heap[best]<heap[i]?best:i;
        if(best==i){
            break;
        }
        swap(heap[best],heap[i]);
        i = best;
        l = i*2+1;
    }
}

//插入操作
void push(int x){
    //底层数组尾部进行插入
    heap[hz] = x;
    //此时hz为有效下标，传入push_up上浮
    push_up(hz);
    //堆大小+1
    hz++;
}

//取出堆顶元素
int top(){
    return heap[0];
}

//删除堆顶元素
//堆化操作，将堆顶元素下沉，维持堆性质
void pop(){
    //堆顶元素与底层数字最末尾元素交换， 堆大小-1表示堆顶被删除了。
    swap(heap[0],heap[--hz]);
    //新堆顶下沉调整， 找到正确的堆顶
    push_down(0);
}
int main(){
    int n,op,x;
    scanf("%d",&n);
    for(int i=0;i<n;++i){
        scanf("%d",&op);
        switch(op){
            case 1:
                scanf("%d",&x);
                push(x);
                break;
            case 2:
                printf("%d\n",top());
                break;
            case 3:
                pop();
        }
    }
    return 0;
}



// #include<bits/stdc++.h>
// using namespace std;

// const int N = 1e6 + 10;
// int heap[N], hz;

// // 插入操作，将元素 x 插入到堆中
// void push(int x) {
//     heap[hz] = x; // 将 x 放到堆的末尾
//     int i = hz;   // 当前插入位置
//     // 向上调整，保证堆性质
//     while (i > 0 && heap[i] < heap[(i - 1) / 2]) {
//         swap(heap[i], heap[(i - 1) / 2]);
//         i = (i - 1) / 2; // 更新到父节点
//     }
//     hz++; // 堆大小 +1
// }

// // 获取堆顶元素
// int top() {
//     if (hz > 0) {
//         return heap[0]; // 返回堆顶
//     } else {
//         throw runtime_error("Heap is empty");
//     }
// }

// // 堆化操作，将堆顶元素下沉，维持堆性质
// void heapify() {
//     int i = 0, l = 1; // l 是左子节点的下标
//     while (l < hz) {
//         // 选择左右子节点中较小的那个
//         int best = (l + 1 < hz && heap[l + 1] < heap[l]) ? l + 1 : l;
//         // 如果子节点更小，则交换
//         best = (heap[best] < heap[i]) ? best : i;
//         if (best == i) {
//             break; // 如果已经满足堆性质，则退出
//         }
//         swap(heap[best], heap[i]);
//         i = best;      // 更新当前节点为交换后的子节点
//         l = i * 2 + 1; // 更新左子节点下标
//     }
// }

// // 删除堆顶元素
// void pop() {
//     if (hz == 0) {
//         throw runtime_error("Heap is empty");
//     }
//     swap(heap[0], heap[--hz]); // 将堆顶与最后一个元素交换，并减小堆大小
//     heapify();                 // 对堆顶进行堆化操作
// }

// int main() {
//     int n, op, x;
//     scanf("%d", &n); // 读取操作的数量
//     hz = 0;          // 初始化堆大小

//     for (int i = 0; i < n; i++) {
//         scanf("%d", &op);
//         switch (op) {
//             case 1: // 插入操作
//                 scanf("%d", &x);
//                 push(x);
//                 break;
//             case 2: // 输出堆顶元素
//                 printf("%d\n", top());
//                 break;
//             case 3: // 删除堆顶元素
//                 pop();
//                 break;
//             default:
//                 throw runtime_error("Invalid operation");
//         }
//     }
//     return 0;
// }