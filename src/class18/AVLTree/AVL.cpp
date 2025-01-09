//fileName： AVL.cpp
//@author: AutumnWhisper.
//@note: AVL树算法模板的静态实现， 仅供学习参考。

//AVL树C++实现
//实现一种结构， 支持如下时间复杂度操作。 单次调用时间复杂度为$O(logn)$
//核心API如下
//add操作， 将关键字x新增入AVL树中， 若重复添加关键字x， 则词频数+1
//remove操作， 若存在多个关键字x，则词频减少一次。 否则考虑从AVL树在移除节点。
//getRank操作， 查询关键字x的排名。注意:x可能不存在AVL树中，但假设其存在找到其排名。
//getIndex操作， 查询排名为x的数字。 注意:测试用例中x一定是有效值。
//pre操作， 查询关键字x的前驱节点关键字。前驱: 小于x且距离最近的关键字。 不存在则返回INT_MIN。(32位整数最小值)
//post操作， 查询关键字x的后继节点关键字。 后继:大于x且距离最近的关键字。 不存在则返回INT_MAX。(32位整数最大值)
//数据范围:
//操作的次数 n <= 10^5
//节点关键字范围-10^7 <= x <= +10^7
//测试链接 : https://www.luogu.com.cn/problem/P3369
//直接提交代码直接通过。

#include<cstdio>
#include<climits>
#include<algorithm>
#include<cstring>
using namespace std;

//函数声明

//up整合子树信息更新当前头节点
void up(int i);
//左旋操作
int leftRotate(int i);
//右旋操作
int rightRotate(int i);
//查询当前值的排名
int getRank(int val);
//查询当前值的排名: 辅助函数
int getRank(int i,int val);
//查询排名为x的关键字
int getIndex(int x);
//查询排名为x的关键字：辅助函数
int getIndex(int i,int x);

//获取节点的前驱节点关键字
int pre(int i);
//pre的辅助函数
int pre(int i,int num);

//获取节点的后继节点关键字
int post(int i);
//post的辅助函数
int post(int i,int num);

void add(int val);
int add(int i,int val);

void remove(int val);
int remove(int i,int val);


//----------------
//字段
const static int N = 1e6+10;

int head = 0;//AVL树的根节点
int cnt = 0;//当前最后使用过节点的编号
int key[N];
int height[N];
int leftChild[N];
int rightChild[N];
int key_count[N];
int size[N];

//更新size,height信息。 根据孩子更新信息
void up(int i){
  size[i] = size[leftChild[i]]+size[rightChild[i]]+key_count[i];
  height[i] = max(height[leftChild[i]], height[rightChild[i]]) + 1;
}

//左旋操作
int leftRotate(int i){
  int r = rightChild[i];
  rightChild[i] = leftChild[r];
  leftChild[r] = i;
  up(i);
  up(r);
  return r;
} 

//右旋操作
int rightRotate(int i){
  int l = leftChild[i];
  leftChild[i] = rightChild[l];
  rightChild[l] = i;
  up(i);
  up(l);
  return l;
}


int maintain(int i){
  int lh = height[leftChild[i]];
  int rh = height[rightChild[i]];
  if(lh-rh>1){
    //L型

    //LL型调整, 对违规节点i进行右旋。
    if(height[leftChild[leftChild[i]]]>=height[rightChild[leftChild[i]]]){
      i = rightRotate(i);
    }else{
      //LR型调整, 先对i左孩子进行左旋， 再对违规节点i进行右旋。
      leftChild[i] = leftRotate(leftChild[i]);
      i = rightRotate(i);
    }
  }else if(rh-lh>1){
    //RR型调整， 对违规节点i进行左旋
    if(height[rightChild[rightChild[i]]]>=height[leftChild[rightChild[i]]]){
      i = leftRotate(i);
    }else{
      //RL型调整， 对i的右孩子进行右旋，再对违规节点i进行左旋。
      rightChild[i] = rightRotate(rightChild[i]);
      i = leftRotate(i);
    }
  }
  return i;
}

int add(int i,int val){
  if(i==0){
    key[++cnt] = val;
    height[cnt] = key_count[cnt] = size[cnt] = 1;
    return cnt;
  }
  if(key[i]==val){
    key_count[i]++;
  }else if(key[i] > val){
    leftChild[i] = add(leftChild[i], val);
  }else{
    rightChild[i] = add(rightChild[i], val);
  }
  up(i);
  return maintain(i);
}
void add(int val){
  head = add(head, val);
}
int removeMostLeft(int i,int mostLeft){
  if(i==mostLeft){
    return rightChild[mostLeft];
  }else{
    leftChild[i] = removeMostLeft(leftChild[i], mostLeft);
    up(i);
    return maintain(i);
  }
}

int remove(int i,int val){
  if(key[i]<val){
    rightChild[i] = remove(rightChild[i], val);
  }else if(key[i] > val){
    leftChild[i] = remove(leftChild[i], val);
  }else{
    if(key_count[i]>1){
      key_count[i]--;
    }else{
      if(leftChild[i]==0&&rightChild[i]==0){
        return 0;
      }else if(leftChild[i]!=0&&rightChild[i]==0){
        i = leftChild[i];
      }else if(leftChild[i]==0&&rightChild[i]!=0){
        i = rightChild[i];
      }else{
        //找右树的最左节点
        int mostLeft = rightChild[i];
        while(leftChild[mostLeft]!=0){
          mostLeft = leftChild[mostLeft];
        }
        //removeMostLeft删除
        rightChild[i] = removeMostLeft(rightChild[i], mostLeft);
        leftChild[mostLeft]=leftChild[i];
        rightChild[mostLeft]=rightChild[i];
        i = mostLeft;
      }
    }
  }
  up(i);
  return maintain(i);
}
void remove(int val){
  if(getRank(val)!=getRank(val+1)){
      head = remove(head, val);
  }
}

int getRank(int val){
  return getRank(head, val)+1;
}

int getRank(int i,int val){
  if(i==0){
    return 0;
  }
  if(key[i]>=val){
    return getRank(leftChild[i], val);
  }else{
    //key[i]<val
    return size[leftChild[i]]+key_count[i]+getRank(rightChild[i], val);
  }
}
int pre(int i,int val){
  if(i==0){
    return INT_MIN;
  }
  if(key[i]>=val){
    return pre(leftChild[i], val);
  }else{
    return max(key[i],pre(rightChild[i],val));
  }
}
int pre(int val){
  return pre(head,val);
}

int post(int i,int val){
  if(i==0){
    return INT_MAX;
  }
  if(key[i]<=val){
    return post(rightChild[i], val);
  }else{
    return min(key[i],post(leftChild[i], val));
  }
}

int post(int val){
  return post(head,val);
}

int getIndex(int i,int x){
  if(size[leftChild[i]]>=x){
    return getIndex(leftChild[i],x);
  }else if(size[leftChild[i]]+key_count[i]<x){
    return getIndex(rightChild[i], x-size[leftChild[i]]-key_count[i]);
  }
  return key[i];
}
int getIndex(int val){
  return getIndex(head, val);
}

void clear(){
  memset(key+1,0, cnt*sizeof(int));
  memset(height+1,0, cnt*sizeof(int));
  memset(leftChild+1,0, cnt*sizeof(int));
  memset(rightChild+1,0, cnt*sizeof(int));
  memset(key_count+1,0, cnt*sizeof(int));
  memset(size+1,0, cnt*sizeof(int));
  cnt = 0;
  head = 0;
}
int main(void){
  int n;
  scanf("%d",&n);
  for(int i=1,op,x;i<=n;i++){
    scanf("%d%d",&op,&x);
    switch(op){
      case 1:
          add(x);
          break;
      case 2:
          remove(x);
          break;
      case 3:
          printf("%d\n", getRank(x));
          break;
      case 4:
          printf("%d\n", getIndex(x));
          break;
      case 5:
          printf("%d\n", pre(x));
          break;
      case 6:
          printf("%d\n", post(x));
          break;
    }
  }
  clear();
  return 0;
}
