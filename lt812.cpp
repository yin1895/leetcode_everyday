#include<bits/stdc++.h>

using namespace std;

struct VecHash {
    size_t operator()(const vector<int>& v) const {
        size_t h = 0;
        for (int x : v) {
            h ^= std::hash<int>()(x) + 0x9e3779b97f4a7c15ULL + (h<<6) + (h>>2);
        }
        return h;
    }
};

struct KeyHash {
    size_t operator()(const vector<vector<int>>& vv) const {
        size_t h = 0;
        for (auto& v : vv) {
            size_t hv = VecHash()(v);
            h ^= hv + 0x9e3779b97f4a7c15ULL + (h<<6) + (h>>2);
        }
        return h;
    }
};

struct KeyEq {
    bool operator()(const vector<vector<int>>& a, const vector<vector<int>>& b) const {
        return a == b;
    }
};

class Solution {
private:
     unordered_map<vector<vector<int>>, double, KeyHash, KeyEq> ump;

public:
    double largestTriangleArea(vector<vector<int>>& points) {
        double ans = 0;
        for(int i = 0;i < points.size();++i)
        {
            for(int j = i+1;j<points.size();++j)
            {
                for(int k = j+1;k<points.size();++k)
                {
                    ans = max(ans,getArea(points[i],points[j],points[k]));
                }
            }
        }

        return ans;
    }

    double getArea(vector<int>&a,vector<int>&b,vector<int>&c)
    {
        vector<vector<int>> k = {a,b,c};
        sort(k.begin(),k.end());

        if(ump.count(k)) return ump[k];

        else
        {
            vector<double> vec1{(double)(b[0]-a[0]),(double)(b[1]-a[1])};
            vector<double> vec2{(double)(c[0]-a[0]),(double)(c[1]-a[1])};

            return ump[k] = 0.5*abs(vec1[0]*vec2[1]-vec2[0]*vec1[1]);
        }
    }
};