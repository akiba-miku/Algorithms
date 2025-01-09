// 两地调度
// 公司计划面试2n个人，给定一个数组 costs
// 其中costs[i]=[aCosti, bCosti]
// 表示第i人飞往a市的费用为aCosti，飞往b市的费用为bCosti
// 返回将每个人都飞到a、b中某座城市的最低费用
// 要求每个城市都有n人抵达
// 测试链接 : https://leetcode.cn/problems/two-city-scheduling/、


class Solution {
public:
    int twoCitySchedCost(vector<vector<int>>& costs) {
        int n = costs.size();
        vector<int> collect(n);
        int idx = 0, sum = 0;
        for(const auto& a:costs){
            collect[idx++] = a[1] - a[0];
            sum += a[0];
        }
        sort(collect.begin(), collect.end());
        for(int i=0;i<n/2;++i){
            sum += collect[i];
        }
        return sum;
    }
};