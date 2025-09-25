#include<bits/stdc++.h>

using namespace std;

class Solution {
private:
    vector<vector<int>> points;
    static bool cmp(vector<int>&p1,vector<int>&p2)
    {
        if(p1[0]==p2[0]) return p1[1]>p2[1];
        else return p1[0] < p2[0];
    }

public:
    int numberOfPairs() {
        int ans = 0;
        print_vec();
        sortVector();
        print_vec();
        for(int i = 0;i<points.size()-1;i++)
        {
            for(int j = i+1;j<points.size();j++)
            {
                
                if(points[j][1]<=points[i][1])
                {
                    bool valid = true;
                    for(int k = i+1;k<j;k++)
                    {
                        if(points[k][1]>=points[j][1]&&points[k][1]<=points[i][1]) valid = false;
                    }
                    if(valid) ans++;
                }
            }
        }
        return ans;
    }

    void sortVector()
    {
        sort(points.begin(),points.end(),cmp);
    }

    void init_vec()
    {
        vector<int> tmp;
        string input;
        getline(cin,input);
        for(auto chr : input)
        {
            if(isdigit(chr)) tmp.push_back(chr - '0');
            if(tmp.size()==2)
            {
                points.push_back(tmp);
                tmp.clear();
            }
        }
    }

    void print_vec()
    {
        for(auto point : points)
        {
            cout << point[0]<<" "<<point[1]<<endl;
        }
    }

    Solution()
    {
        init_vec();
        cout << numberOfPairs()<<endl;
    }
};

int main()
{
    Solution question;
    return 0;
}