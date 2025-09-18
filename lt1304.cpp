#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<int> sumZero(int n) {
        vector<int> ans;
        if(n%2==1)
        {
            ans.push_back(0);
            for(int i = 0;i<n/2;i++)
            {
                ans.push_back(i+1);
                ans.push_back(-i-1);
            }
        }
        else
        {
            for(int i = 0;i<n/2;i++)
            {
                ans.push_back(i+1);
                ans.push_back(-i-1);
            }
        }
        return ans;
    }
    Solution(int n)
    {
        vector<int> ans = sumZero(n);
        for(const auto &it : ans)
        {
            cout << it <<' ';
        }
    }
};

int main()
{
    int n = 0;
    cin >> n;
    Solution question(n);
    return 0;
}