#include<string>
#include<iostream>
#include<algorithm>

using namespace std;

const int N = 1691968;//1691968下界, 数据范围欺诈
//小写字母
//'a'->0
//'b'->1
//...
//'z'->25
//大写字母
//'A'->26
//'B'->27
//...
//'Z'->51 26+up_char-'A'
//数字
//'0'->52 52+number-'0'
//'1'->53
//...
//'9'->61

//输入c是数字，小写字母，大写字母。
inline int index(char c){
	if(c>='a'&&c<='z') return c-'a';
	else if(c>='A'&&c<='Z') return c-'A'+26;
	else return c-'0'+52;
}

int cnt;
//只包含小写字母 26
//包含大小写字母 52 26+26
//包含大小写字母 62 26+26+10
//ASCII码 128
//多字符集用静态空间哈希表。每次测试完清空哈希表数组
//更多，按位分路。
const int M = 62;
int tree[N][62];//26+26+10
int prefix_cnt[N], words_cnt[N];
//"创建"前缀树：重置节点编号
inline void build(){cnt=1;}
//清除前缀树
void clear(){
	for(int i=1;i<=cnt;i++){
		fill(tree[i],tree[i]+62,0);
		prefix_cnt[i]=0;
		words_cnt[i]=0;
	}
}

//将字符串word添加到前缀树中
//若word重复则增加"词频"
void insert(const string& word){
	int cur = 1;
	prefix_cnt[cur]++;
	for(int i=0,path;i<word.size();i++){
		path=index(word[i]);
		if(tree[cur][path]==0){
			tree[cur][path]=++cnt;
		}
		cur = tree[cur][path];
		prefix_cnt[cur]++;
	}
	words_cnt[cur]++;
}

//查询word作为字符串数组的前缀数量
int prefix(const string& word){
	int cur = 1;
	for(int i=0,path;i<word.size();i++){
		path=index(word[i]);
		if(tree[cur][path]==0){
			return 0;
		}
		cur = tree[cur][path];
	}
	return prefix_cnt[cur];
}

//查询字符串word出现的次数
int search(const string& word){
	int cur = 1;
	for(int i=0,path;i<word.size();i++){
		path=index(word[i]);
		if(tree[cur][path]==0){
			return 0;
		}
		cur=tree[cur][path];
	}
	return words_cnt[cur];
}

//删除字符串word出现的次数
void erase(const string& word){
	if(search(word)==0) return ;
	int cur = 1;
	prefix_cnt[cur]--;
	for(int i=0,path;i<word.size();i++){
		path=index(word[i]);
		if(--prefix_cnt[tree[cur][path]]==0){
			tree[cur][path]=0;
			return ;
		}
		cur = tree[cur][path];
	}
	words_cnt[cur]--;
}


int t,n,q;
string s;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>t;
	int i,j;
	for(i=0;i<t;i++){
		cin>>n>>q;
		build();
		for(j=0;j<n;j++){
			cin>>s;
			insert(s);
		}
		for(j=0;j<q;j++){
			cin>>s;
			cout<<prefix(s)<<endl;
		}
		clear();
	}
	return 0;
}