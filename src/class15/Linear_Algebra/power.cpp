#include<bits/stdc++.h>
using namespace std;


//矩阵乘法:O(n^3)
//左列等于右行
vector<vector<int>> multiply(vector<vector<int>> a,vector<vector<int>> b){
  int n = a.size();//左行
  int m = b[0].size();//右列
  int k = a[0].size();
  vector<vector<int>> ans(n, vector<int>(m,0));
  for(int i=0;i<n;i++){
    for(int j=0;j<m;j++){
      for(int c=0;c<k;c++){
        ans[i][j] += a[i][c] * b[c][j];
      }
    }
  }
  return ans;
} 

//矩阵求幂:矩阵快速幂 O(k^3*logn)
//方阵，正方形矩阵。
vector<vector<int>> power(vector<vector<int>> a,int b){
  int n = a.size();
  vector<vector<int>> ans(n, vector<int>(n,0));
  for(int i=0;i<n;i++){
    ans[i][i] = 1;
  }
  while(b){
    if(b&1){
      ans = multiply(ans,a);
    }
    a = multiply(a,a);
    b >>= 1;
  }
  return ans;
}

// Print 2D matrix
void print(const vector<vector<int>>& m) {
    for (const auto& row : m) {
        for (int val : row) {
            cout << val << "\t";
        }
        cout << endl;
    }
}

// Matrix exponentiation demonstration
void f2() {
    vector<vector<int>> a = {{1, 2}, {3, 4}};
    auto b = multiply(a, multiply(a, multiply(a, multiply(a, a))));
    print(b);
    cout << "======" << endl;

    print(power(a, 5));
}

// Solve Fibonacci nth term using matrix multiplication
void f3() {
    vector<vector<int>> start = {{1, 0}};
    vector<vector<int>> m = {{1, 1}, {1, 0}};
    auto a = multiply(start, m);
    print(a);
    cout << "======" << endl;

    auto b = multiply(a, m);
    print(b);
    cout << "======" << endl;

    auto c = multiply(b, m);
    print(c);
    cout << "======" << endl;

    auto d = multiply(c, m);
    print(d);
}

// Solve Fibonacci nth term using matrix exponentiation
void f4() {
    vector<vector<int>> start = {{1, 0}};
    vector<vector<int>> m = {{1, 1}, {1, 0}};
    auto a = multiply(start, power(m, 1));
    print(a);
    cout << "======" << endl;

    auto b = multiply(start, power(m, 2));
    print(b);
    cout << "======" << endl;

    auto c = multiply(start, power(m, 3));
    print(c);
    cout << "======" << endl;

    auto d = multiply(start, power(m, 4));
    print(d);
}

int main() {
    cout << "f2() : " << endl;
    cout << "Matrix exponentiation demonstration begins" << endl;
    f2();
    cout << "Matrix exponentiation demonstration ends" << endl;
    cout << endl;

    cout << "f3() : " << endl;
    cout << "Solve Fibonacci nth term using matrix multiplication" << endl;
    cout << "Demonstration begins" << endl;
    f3();
    cout << "Demonstration ends" << endl;
    cout << endl;

    cout << "f4() : " << endl;
    cout << "Solve Fibonacci nth term using matrix exponentiation" << endl;
    cout << "Demonstration begins" << endl;
    f4();
    cout << "Demonstration ends" << endl;
    cout << endl;

    return 0;
}