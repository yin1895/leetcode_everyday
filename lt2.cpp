//leetcode 3000. 对角线最长的矩形的面积
#include<iostream>
#include<vector>
#include<cctype>
#include<string>
#include<cmath>

using namespace std;

class Solution{
    private:
        vector<vector<int>> dimensions;

    public:
        void init_vec()
        {
            string input;
            getline(cin,input);
            vector<int> line;
            string tmp;
            for(auto chunk : input)
            {
                if(isdigit(chunk))
                {
                    tmp+=chunk;
                }
                else if(chunk == ','&&!tmp.empty())
                {
                    line.push_back(stoi(tmp));
                    tmp.clear();
                }
                else if(chunk == ']')
                {
                    if(!tmp.empty())
                    {
                        line.push_back(stoi(tmp));
                        tmp.clear();
                        this->dimensions.push_back(line);
                        line.clear();
                    }
                }
            }
        }

        void print_vec_vec()
        {
            for(auto line : this->dimensions)
            {
                for(auto chunk : line)
                {
                    cout << chunk<<" ";
                }
                cout << endl;
            }
        }

        Solution()
        {
            init_vec();
            print_vec_vec();
        }

       int areaOfMaxDiagonal(vector<vector<int>>& dimensions) {
        int dui = dimensions[0][0]*dimensions[0][0]+dimensions[0][1]*dimensions[0][1];
        int area = dimensions[0][0]*dimensions[0][1];
        for(auto line : dimensions)
        {
            if(line[0]*line[0]+line[1]*line[1]>dui)
            {
                dui = line[0]*line[0]+line[1]*line[1];
                area = line[0]*line[1];
            }
            else if(line[0]*line[0]+line[1]*line[1]==dui){
                area = area > (line[0]*line[1])?area:(line[0]*line[1]);
            }
        }
        return area;
    }
};

int main()
{
    Solution s1;
}