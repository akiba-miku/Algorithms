#include<bits/stdc++.h>
using namespace std;
const int MAXN = 11000001;
char ss[MAXN<<1];
int p[MAXN<<1];
int n;


void manacherss(const string& s){
    int i=0,j=0;
    n=s.size()*2+1;
    for(;i<n;++i) ss[i]=i%2==0?'#':s[j++];
}
int manacher(const string& s){
    manacherss(s);
    int max_r = 0;
    for(int i=0,c=0,r=0,len;i<n;++i){
        len=r>i?min(p[2*c-i],r-i):1;
        while(i+len<n&&i-len>=0&&ss[i-len]==ss[i+len]) ++len;
        if(i+len>r){
            r = i + len;
            c = i;
        }
        max_r = max(max_r, len);
        p[i] = len;
    }
    return max_r-1;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    string s;
    getline(cin, s);
    cout<<manacher(s)<<'\n';

}