#include<iostream>
#include<vector>
#include<string>
#include<cctype>
#include<algorithm>

using namespace std;

class Solution {
private:
    vector<vector<int>> mat;
    vector<vector<vector<int>>> restoreOfAllWays;
public:
    int lenOfVDiagonal(vector<vector<int>>& grid) {
        grid = this->mat;
        this->restoreOfAllWays.clear();

        from1ToRstore();

        vector<vector<vector<int>>> allowedWays = selectAllowedWay();

        if(allowedWays.empty()) return 0;

        vector<int> length;
        for(const auto& way : allowedWays)
        {
            length.push_back(way.size());
        }

        sort(length.begin(),length.end());

        return length.back();
    }

    

    void from1ToRstore()
    {
        
        for(int i = 0;i<mat.size();i++)
        {
            for(int j = 0;j<mat[0].size();j++)
            {
                vector<vector<int>> xy;
                if(mat[i][j]==1)
                {
                    bool aimNumIsTwo=true;
                    vector<vector<int>> isReachedXy;
                    xy.push_back({i,j});
                    isReachedXy.push_back({i,j});

                    dfsFrom2(xy,aimNumIsTwo,isReachedXy);

                    isReachedXy.pop_back();
                    xy.pop_back();
                }
            }
        }
    }

    bool nextStepWasReached(int x,int y,vector<vector<int>>&isReachedXy)
    {
        for(auto index:isReachedXy)
        {
            if(index[0]==x&&index[1]==y) return true;
        }

        return false;
    }

    void dfsFrom2(vector<vector<int>>&xy,bool aimNumIsTwo,vector<vector<int>>&isReachedXy)
    {
        int aimNum = aimNumIsTwo?2:0;
        int x0 = xy.back()[0];
        int y0 = xy.back()[1];

        int dx[] = {-1,-1,1,1};
        int dy[] = {-1,1,-1,1};

        vector<vector<int>> toDetect;

        for(int i = 0;i<4;i++)
        {
            int x= x0+dx[i];
            int y= y0+dy[i];

            if(!nextStepWasReached(x,y,isReachedXy))
            {
                 
                if(x>=0&&x<mat.size()&&y>=0&&y<mat[0].size())
                {
                    if(mat[x][y]==aimNum) toDetect.push_back({x,y});
                }
            }
        }

        if(toDetect.empty())
        {
            restoreOfAllWays.push_back(xy);
            return;
        }

        for(const auto& nextStep : toDetect)
        {
            xy.push_back(nextStep);
            isReachedXy.push_back(nextStep);

            dfsFrom2(xy,!aimNumIsTwo,isReachedXy);

            isReachedXy.pop_back();
            xy.pop_back();
        }
    }

    vector<vector<vector<int>>> selectAllowedWay()
        {
            vector<vector<vector<int>>> allowedWays;
            for(const auto& way : restoreOfAllWays)
            {
                if(way.size()==1)
                {
                    if(mat[way[0][0]][way[0][1]]==1) allowedWays.push_back(way);
                }

                if(way.size()==2) allowedWays.push_back(way);

                if(way.size()>=3)
                {
                    int turnedTimes = 0;
                    bool isAllowed = true;
                    for(int step = 2;step<way.size();step++)
                    {
                        double prev_k = (way[step-2][1]-way[step-1][1])/(way[step-2][0]-way[step-1][0]);
                        double k = (way[step-1][1]-way[step][1])/(way[step-1][0]-way[step][0]);
                        if(prev_k != k)
                        {
                            turnedTimes++;
                            if(turnedTimes>1) isAllowed = false;
                            if(-(way[step-2][1]-way[step-1][1])+way[step-1][0]!=way[step][0]) isAllowed = false;//需要满足一个点按照另一个点逆时针旋转90°后对于的坐标，否则无法保证前进方向的旋转是顺时针90°
                        }
                    }
                    if(isAllowed) allowedWays.push_back(way);
                }
            }
            return allowedWays;
        }
};


