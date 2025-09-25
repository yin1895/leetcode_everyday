#include<bits/stdc++.h>

using namespace std;

class Solution {
private:
    static bool cmp(vector<int>&p1,vector<int>&p2)
    {
        if(p1[0]==p2[0]) return p1[1]>p2[1];
        else return p1[0] < p2[0];
    }

public:
    int numberOfPairs(vector<vector<int>>& points) {
        sortPoints(points);
        const int n = (int) points.size();
        long long ans = 0;
        for(int i = 0;i<n-1;i++)
        {
            const int yi = points[i][1];
            deque<int> dq;

            for(int j =i+1;j<n;j++)
            {
                const int yj = points[j][1];

                if(yj<=yi)
                {
                    if(dq.empty() || dq.front() < yj) ++ans;
                while(!dq.empty()&&dq.back()<=yj) dq.pop_back();
                dq.push_back(yj);
                }
            }
        }
        return static_cast<int>(ans);
    }

    void sortPoints(vector<vector<int>>&points)
    {
        sort(points.begin(),points.end(),cmp);
    }
};