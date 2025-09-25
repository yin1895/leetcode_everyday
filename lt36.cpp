#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        return (lineIsValid(board)&&rowIsValid(board)&&chunkisValid(board));
    }

    bool lineIsValid(vector<vector<char>>& board)
    {
        for(auto line : board)
        {
            vector<int> iterator(9,0);
            for(auto num : line)
            {
                if(num!='.') iterator[num-1-'0']++;
            }
            for(auto iter : iterator)
            {
            if(iter>1) return false;
            }
        }

        return true;
    }

    bool rowIsValid(vector<vector<char>>& board)
    {
        
        for(int i = 0;i<9;i++)
        {
            vector<int> iterator(9,0);
            for(int j = 0;j<9;j++)
            {
                if(board[j][i]!='.') iterator[board[j][i]-1-'0']++;
            }

            for(auto iter : iterator)
            {
            if(iter>1) return false;
            }
        }

        return true;
    }

    bool chunkisValid(vector<vector<char>>& board)
    {
        
        for(int chunkx = 0;chunkx<3;chunkx++)
        {
            for(int chunky = 0;chunky<3;chunky++)
            {
                vector<int> iterator(9,0);
                for(int x = 0;x<3;x++)
                {
                    for(int y = 0;y<3;y++)
                    {
                        char tmp = board[x+3*chunkx][y+3*chunky];
                        if(tmp!='.') iterator[tmp-1-'0']++;
                    }
                }
                for(auto iter : iterator)
                {
                    if(iter > 1) return false;
                }
            }
        }       
        return true;
    }
};