#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        deque<int> dq;
        double ans = 0;
        double tmp = 0;
        for(int i =0;i<k;i++)
        {
            tmp += double(nums[i]);
            dq.push_back(nums[i]);
        }
        ans = tmp / k;
        for(int i = k;i<nums.size();i++)
        {
            tmp-=dq.front();
            dq.pop_front();
            dq.push_back(nums[i]);
            tmp+=dq.back();
            ans = tmp/k > ans ? tmp/k : ans;
        }
        return ans;
    }
};