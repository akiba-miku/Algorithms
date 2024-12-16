#include<algorithm>
const int N = 1e5+10;
int stack_arr[N];
int r;
class Solution {
public:
    int largestRectangleArea(vector<int>& h) {
        r = 0;
        int n = h.size();
        int ans = 0;
        for(int i=0;i<n;++i){
            while(r>0&&h[stack_arr[r-1]]>=h[i]){
                int pos = stack_arr[--r];
                int l = r>0?stack_arr[r-1]:-1;
                ans = max(ans, (i-l-1)*h[pos]);
            }
            stack_arr[r++]=i;
        }
        while(r>0){
            int pos = stack_arr[--r];
            int l = r>0?stack_arr[r-1]:-1;
            ans = max(ans, (n-l-1)*h[pos]);
        }
        return ans;
    }
};