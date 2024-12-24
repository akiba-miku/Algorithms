/**
 * 栈的特点是后进先出， 它是一种特殊的线性表， 可以认为是一种行为限制的数组。
 * 以下是静态数组实现栈。 存储连续且速度快， 因为在内存的静态区。 
 * 事实上一个静态数组可以充当栈， 并且完全不需要类或者结构体封装。 只要理解对应底层数组的操作即可。
 * 动态扩容或者链表实现(非数组实现链表)的会在堆中开内存。 速度比静态慢，C语言实现要用malloc,realloc,free函数。
 * 
 */
#include<stdio.h>
#include<stddef.h>
#include<stdlib.h>
#define MAXN 10001
typedef struct Stack{
    int array[MAXN];
    int top;
}Stack;

void init(Stack* st){
    st->top = 0;
}

void push(Stack *st, int val){
    if(st->top>MAXN){
        printf("Stack OverFlow!\n");
        return ;
    }
    st->array[st->top++]=val;
}

void pop(Stack* st){
    if(st->top==0){
        printf("Stack DownFlow\n");
        exit(-1);
    }
    st->top--;
}

int top(Stack* st){
    if(st->top==0){
        printf("Stack DownFlow\n");
        exit(-1);
    }
    return st->array[st->top-1];
}

/**
测试开始
入栈序列:1 2 3 4
出栈序列:
4
3
2
1
测试结束
 */
int main(){
    printf("测试开始\n");
    printf("入栈序列:1 2 3 4\n");
    Stack stack;
    init(&stack);
    //输入序列[1,2,3,4]
    push(&stack, 1);
    push(&stack, 2);
    push(&stack, 3);
    push(&stack, 4);

    printf("出栈序列:\n");
    while(stack.top!=0){
        printf("%d\n",top(&stack));
        pop(&stack);
    }
    printf("测试结束\n");
    return 0;
}
