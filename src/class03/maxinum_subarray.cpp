#include <vector>
#include <climits>
using namespace std;

class Solution {
public:
    int left;
    int right;
    int sum;

    void maxSubArray(vector<int>& nums) {
        sum = INT_MIN;
        int n = nums.size();
        for(int l=0,r=0,pre=INT_MIN;r<n;r++){
            if(pre>=0) pre+=nums[r];
            else {
                pre = nums[r];
                l = r;
            }
            if(pre>sum){
                left = l;
                right = r;
                sum = pre;
            }
        }
    }
};


//java版本

// import java.util.*;

// class Solution {
//     public int left;
//     public int right;
//     public int sum;

//     public void maxSubArray(int[] nums) {
//         sum = Integer.MIN_VALUE;
//         int n = nums.length;
//         for (int l = 0, r = 0, pre = Integer.MIN_VALUE; r < n; r++) {
//             if (pre >= 0) {
//                 pre += nums[r];
//             } else {
//                 pre = nums[r];
//                 l = r;
//             }
//             if (pre > sum) {
//                 left = l;
//                 right = r;
//                 sum = pre;
//             }
//         }
//     }
// }
