#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    int maxFrequencyElements(vector<int>& nums) {
        unordered_map<int,int> cnt;
        int maxFreq = 0;

        for (int num : nums) {
            cnt[num]++;
            maxFreq = max(maxFreq, cnt[num]);
        }

        int ans = 0;
        for (auto& [k,v] : cnt) {
            if (v == maxFreq) ans += v;
        }
        return ans;
    }
};
