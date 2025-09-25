#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<int> getNoZeroIntegers(int n) {
        vector<int> ans;
        for(int i = 1;i<=n/2;i++)
        {
            if(isValidNum(i)&&isValidNum(n-i))
            {   
                ans.push_back(i);
                ans.push_back(n-i);
                break;
            }
        }

        return ans;
    }

    bool isValidNum(int num)
    {
        string input = to_string(num);
        for(const auto &chr : input)
        {
            if(chr == '0') return false;
        }

        return true;
    }
};