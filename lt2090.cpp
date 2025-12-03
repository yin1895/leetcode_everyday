#include<bits/stdc++.h>
using namespace std;

class Solution{
public:
    vector<int> getAverages(vector<int>& nums, int k){
        int n = (int)nums.size();
        int window = 2*k+1;
        vector<int> ans(n, -1);
        if(n< window)return ans;

        long long sum=0;
        for(int i = 0;i< n;++i){
            sum+=nums[i];
            if(i >= window){
                sum -= nums[i-window];
            }
            if(i >= window - 1){
                int center = i - k;
                ans[center] = (int)(sum/window);
            }
        }
        return ans;
    }

};