//失败版本，由于递归部分逻辑太过庞杂还有终止条件的不明确
//lt 3459
#include<iostream>
#include<vector>
#include<string>
#include<cctype>
#include<algorithm>

using namespace std;

class Solution {
private:
    vector<vector<int>> grid;

public:
    int lenOfVDiagonal() {
        //储存所有的可能的路线
        //from1ToDfs()->restoreOfAllXy
        //selectTheLonggestWay()->return ans.back()/0
        vector<vector<vector<int>>> restoreOfAllXy = from1ToDfs();

        return selectTheLonggestWay(restoreOfAllXy);
    }

    void init_grid()
    {
        string input;
        getline(cin,input);
        string num;
        vector<int> line_num;

        for(auto chr : input)
        {
            if(isdigit(chr)) num+=chr;

            if(chr==','&&!num.empty())
            {
                line_num.emplace_back(stoi(num));
                num.clear();
            }
            if(chr==']'&&!line_num.empty())
            {
                line_num.emplace_back(stoi(num));
                this->grid.push_back(line_num);
                line_num.clear();
                num.clear();
            }
        }
    }

    void print_grid()
    {
        for(auto line : this->grid)
        {
            for(auto chunk : line)
            {
                cout << chunk << " ";
            }
            cout << endl;
        }
    }

    int selectTheLonggestWay(vector<vector<vector<int>>>&restoreOfAllXy)
    {
        vector<int> ans;
        for(auto chunk : restoreOfAllXy)
        {
            ans.push_back(chunk.size());
        }
        sort(ans.begin(),ans.end());

        return ans.empty()?0:ans.back();
    }

    vector<vector<vector<int>>> from1ToDfs()
    {
        vector<vector<vector<int>>>restoreOfAllXy;

        for(int i = 0;i<this->grid.size();i++)
        {
            for(int j = 0;j<this->grid[0].size();j++)
            {
                if(this->grid[i][j]==1)
                {
                    vector<vector<int>> xy;
                    xy.push_back({i,j});//在这里假设题目给出的是一个严格矩形，从起点“1”开始记录坐标
                    bool ableToTurnRight=1;//只可以顺时针转90，设计一个状态机
                    DFS_2To0(restoreOfAllXy,xy,ableToTurnRight);
                    xy.clear();
                }
            }
        }
        return restoreOfAllXy;
    }

    void DFS_2To0(vector<vector<vector<int>>>&restoreOfAllXy,vector<vector<int>>&xy,bool ableToTurnRight)
    {
        int x0 = xy.back()[0];
        int y0 = xy.back()[1];//这是每一次移动的起点

        int dx[] = {-1,-1,1,1};
        int dy[] = {-1,1,-1,1};

        vector<vector<int>> toDetect;

        for(int i = 0;i<4;i++)
        {
            int x = x0+dx[i];
            int y = y0+dy[i];

            if(x>=0&&x<this->grid.size()&&y>=0&&y<this->grid[0].size())//广度优先，判断四角是否合法
            {
                toDetect.push_back({x,y});
            }
        }
        

        //终止条件判断，即无法步进，须满足条件：
        //1.存在邻居
        //2.可以到达，必须没有到达过
        //3.若可以转弯则指定的邻居必须存在
        //4.不可转弯则指定邻居也得在
        //5.必须满足2->0->2...的循环
        bool nextIsTwo = true;
        int aimNum = nextIsTwo ? 2: 0;
        bool isEnd = true;
        if(toDetect.empty()) isEnd = true;
        else{
            if(xy.size()==1) //如果是最开始的起点1，那么只要存在2的邻居就不是终点
            {
                for(auto index : toDetect)
                {
                    if(this->grid[index[0]][index[1]]==2) 
                    {
                        isEnd =false;
                        break;
                    }
                }
            }
            else{
                if(ableToTurnRight)
                {
                    //两种选择，转或者不转
                    int target_x1 = -(xy[xy.size()-2][1]-y0)+x0;
                    int target_y1 = xy[xy.size()-2][0]-x0+y0;
                    //上面是转所对应的下一个点的坐标

                    int target_x2 = 2*x0-xy[xy.size()-2][0];
                    int target_y2 = 2*y0-xy[xy.size()-2][1];
                    //上面是不转所对应的下一个坐标

                    for(auto index : toDetect)
                    {
                        if((index[0]==target_x1&&index[1]==target_y1)||(index[0]==target_x2&&index[1]==target_y2))
                        {
                            if(grid[index[0]][index[1]]!=grid[x0][y0])
                            {
                                isEnd = false;
                                break;
                            }
                        }

                    }
                }
                else{
                    int target_x2 = 2*x0-xy[xy.size()-2][0];
                    int target_y2 = 2*y0-xy[xy.size()-2][1];

                    for(auto index : toDetect)
                    {
                        if(index[0]==target_x2&&index[1]==target_y2)
                        {
                            if(grid[index[0]][index[1]]!=grid[x0][y0])
                            {
                                isEnd = false;
                                break;
                            }
                        }

                    }
                }
                
            }
        }

        for(auto point : toDetect)
        {
            if(this->grid[point[0]][point[1]]==aimNum)
            {
                vector<vector<bool>> ableToReach(this->grid.size(),vector<bool>(this->grid[0].size(),true));
                ableToReach[x0][y0] = false;
                xy.push_back(point);
                ableToReach[point[0]][point[1]] = false;
                DFS_2To0(restoreOfAllXy,xy,!ableToTurnRight);
                xy.pop_back();
            }
        }
        if(isEnd)
        {
            restoreOfAllXy.push_back(xy);
            return;
        }
    }

    Solution()
    {
        init_grid();
        print_grid();
        cout << lenOfVDiagonal()<<endl;
    }

};

int main()
{
    Solution s1;
    return 0;
}