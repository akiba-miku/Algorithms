#include<vector>
#include<cstdio>
#include<iostream>
#include<string>
using namespace std;

vector<int> mul(vector<int>& a, vector<int>& b){
	int n1 = a.size(), n2 = b.size();
	vector<int> c(a.size()+b.size(),0);
	for(int i=0;i<n1;i++){
		for(int j=0;j<n2;j++){
			c[i+j] += a[i]*b[j];
		}
	}
	for(int i=0,t=0;i<c.size()||t;i++){
    if(i<c.size()){
      t += c[i];
      c[i] = t%10;
    }else{
      c.push_back(t%10);
    }
    t /= 10;
	}
	while(c.size()>1&&c.back()==0){
		c.pop_back();
	}
	return c;
}

int main(void){
	ios::sync_with_stdio(0);
	cin.tie(0);

  string a,b;
  cin>>a>>b;
	vector<int> A,B;
	for(int i=a.size()-1;i>=0;i--) A.push_back(a[i]-'0');
	for(int i=b.size()-1;i>=0;i--) B.push_back(b[i]-'0');
	auto C = mul(A,B);
	for(int i=C.size()-1;i>=0;i--){
		printf("%d",C[i]);
	}
	putchar('\n');
	return 0;
}