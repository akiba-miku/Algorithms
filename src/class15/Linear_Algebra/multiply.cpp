#include<bits/stdc++.h>
using namespace std;

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


// Print 2D matrix
void print(const vector<vector<int>>& m) {
    for (const auto& row : m) {
        for (int val : row) {
            cout << val << "\t";
        }
        cout << endl;
    }
}

// Matrix multiplication demonstration
void f1() {
    vector<vector<int>> a = {{1, 3}, {4, 2}};
    vector<vector<int>> b = {{2, 3}, {3, 2}};
    printf("a:\n");
    print(a);
    printf("b:\n");
    print(b);
    printf("ans1:\n");
    auto ans1 = multiply(a, b);
    print(ans1);
    cout << "==============" << endl;

    vector<vector<int>> c = {{2, 4}, {3, 2}};
    vector<vector<int>> d = {{2, 3, 2}, {3, 2, 3}};
    printf("c:\n");
    print(c);
    printf("d:\n");
    print(d);
    printf("ans2:\n");
    auto ans2 = multiply(c, d);
    print(ans2);
    cout << "==============" << endl;

    vector<vector<int>> e = {{2, 4}, {1, 2}, {3, 1}};
    vector<vector<int>> f = {{2, 3}, {4, 1}};
    printf("e:\n");
    print(e);
    printf("f:\n");
    print(f);
    printf("ans3:\n");
    auto ans3 = multiply(e, f);
    print(ans3);
    cout << "==============" << endl;

    vector<vector<int>> g = {{3, 1, 2}};
    vector<vector<int>> h = {{1, 2, 1}, {3, 2, 1}, {4, 2, -2}};
    printf("g:\n");
    print(g);
    printf("h:\n");
    print(h);
    printf("ans4:\n");
    auto ans4 = multiply(g, h);
    print(ans4);
}


int main() {
    cout << "f1() : " << endl;
    cout << "Matrix multiplication demonstration begins" << endl;
    f1();
    cout << "Matrix multiplication demonstration ends" << endl;
    cout << endl;
    return 0;
}