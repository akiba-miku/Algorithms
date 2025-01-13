#include<cstdio>

const int N = 1e6+10;
int head;//头指针
int cnt;//节点空间使用编号
int e[N];//下标：节点编号 数组值:节点存储的值
int ne[N];//下标：节点编号 数组值：节点之后的下一个节点编号


//interface
void init(){
  head=0;//0编号留作结束标记
  cnt=1;//空间编号从1开始使用
}

//头插法:O(1)
void add_to_head(int x){
  e[cnt]=x;
  ne[cnt]=head;
  head=cnt++;
}

//删除k编号之后的节点
//若k==0，这意味删除头节点
void delete_after_k(int k){
  if(!k){
    head=ne[head];
  }else{
    ne[k]=ne[ne[k]];
  }
}

//在编号的节点后插入一个新节点
void add_after_k(int k,int x){
  if(!k) add_to_head(x);
  else{
    e[cnt]=x;
    ne[cnt]=ne[k];
    ne[k]=cnt++;
  }
}

