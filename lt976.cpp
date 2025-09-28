#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int largestPerimeter(vector<int>& nums) {
        sort(nums.begin(), nums.end(), greater<int>()); // 从大到小排
        for (int i = 0; i + 2 < nums.size(); ++i) {
            if (nums[i+1] + nums[i+2] > nums[i]) { 
                return nums[i] + nums[i+1] + nums[i+2]; 
            }
        }
        return 0;
    }
};
