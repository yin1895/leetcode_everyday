#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    Solution()
        : row(9, vector<bool>(10, false)),
          col(9, vector<bool>(10, false)),
          chunk(9, vector<bool>(10, false)) {}

    void solveSudoku() {
        init_board();
        solve(0,0);
        print_board();
    }
private:
    vector<vector<bool>> row;
    vector<vector<bool>> col;
    vector<vector<bool>> chunk;
    vector<vector<char>> board;

    void init_board() {
        board.resize(9, vector<char>(9));
        string s;
        getline(cin, s);  // 读整行
        int i = 0, j = 0;
        for (char c : s) {
            if (c == '.' || (c >= '1' && c <= '9')) {
                board[i][j] = c;
                j++;
                if (j == 9) { j = 0; i++; }
            }
        }
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] != '.') {
                    int d = board[i][j] - '0';
                    row[i][d] = col[j][d] = chunk[(i/3)*3 + (j/3)][d] = true;
                }
        }
}

    }

    void print_board() {
        cout << "[";
        for (int i = 0; i < 9; i++) {
            cout << "[";
            for (int j = 0; j < 9; j++) {
                cout << "\"" << board[i][j] << "\"";
                if (j < 8) cout << ",";
            }
            cout << "]";
            if (i < 8) cout << ",";
            cout << endl;
        }
        cout << "]" << endl;
    }

    bool solve(int x=0,int y=0)
    {
        if(x == 9) return true;
        if(y == 9) return solve(x+1,0);
        
        if(board[x][y]!='.') return solve(x,y+1);

        for(int i = 1;i<=9;i++)
        {
            if(!row[x][i]&&!col[y][i]&&!chunk[(x/3)*3+(y/3)][i])
            {
                board[x][y] = i+'0';
                row[x][i]=col[y][i]=chunk[(x/3)*3+(y/3)][i]=true;

                if(solve(x,y+1)) return true;

                board[x][y] = '.';
                row[x][i]=col[y][i]=chunk[(x/3)*3+(y/3)][i]=false;
            }
        }
        return false;
    }

};

int main()
{
    Solution question;
    question.solveSudoku();
}