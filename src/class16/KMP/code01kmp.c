#include<stdio.h>
#include<ctype.h>
#include<stddef.h>
#include<string.h>
#define N 10010
#define M 10010
char str[N], match[M];
char next[N];
int n,m;

static void get_next_arr(const char* s,int n){
    next[0]=-1, next[1]=0;
    if(n<=2) return ;
    int i=2,pre=0;
    while(i<n){
        if(s[i-1]==s[pre]) next[i++]=++pre;
        else if(pre>0) pre=next[pre];
        else next[i++]=0;
    }
}
int kmp(const char* str,const char* match){
    n = strlen(str), m = strlen(match);
    get_next_arr(match, m);
    int i,j;
    for(i=0,j=0;i<n&&j<m;){
        if(str[i]==match[j]) ++i,++j;
        else if(j==0) ++i;
        else j=next[j];
    }
    return j==m?i-j:-1;
}

int main(){
    fgets(str,sizeof(str), stdin);
    fgets(match, sizeof(match), stdin);
    int idx = kmp(str,match);
    if(idx==-1){
        printf("str中不存在match子串\n");
    }else{
        printf("str中第一次出现match子串的下标:%d\n", idx);
    }
    return 0;
}