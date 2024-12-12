#include<bits/stdc++.h>
using namespace std;
vector<int> next_array(const string& s, int n);
int kmp(const string& str, const string& match){
    int n = str.length(), m = match.length();
    vector<int> next = next_array(match, m);
    int i=0,j=0;
    while(i<n&&j<m){
        if(str[i]==match[j]) ++i,++j;
        else if(j==0) ++i;
        else j=next[j];
    }
    return j==m?i-j:-1;
}
//求s串的next数组
vector<int> next_array(const string& s, int n){
    if(n==1) return vector<int> {-1};
    vector<int> next(n);
    next[0]=-1,next[1]=0;
    for(int i=2,pre=0;i<n;){
        if(s[i-1]==s[pre]) next[i++]=++pre;
        else if(pre!=-1) pre=next[pre];
        else next[i++]=0;
    }
    return next;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    string str, match;
    getline(cin, str);
    getline(cin, match);
    int idx = kmp(str, match);
    if(idx==-1){
        cout<<"str不存在子串match"<<'\n';
    }else{
        printf("str第一次出现match串的下标:%d\n", idx);
    }
    return 0;
}