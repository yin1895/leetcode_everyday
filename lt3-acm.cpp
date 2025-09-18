#include<bits/stdc++.h>
using namespace std;

class Solution {
private:
    vector<vector<int>> grid;

public:
    int lenOfVDiagonal() {
       

        if (grid.empty() || grid[0].empty()) {
            return 0;
        }

        int n = grid.size();
        int m = grid[0].size();
        int max_len = 0;

        // 检查网格中是否有'1'。如果有，最小长度就是1。
        bool has_one = false;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == 1) {
                    has_one = true;
                    break;
                }
            }
            if (has_one) break;
        }
        
        if (!has_one) return 0; // 如果连1都没有，直接返回0
        max_len = 1; // 否则，最少是1

        // 定义4个对角线方向: {行变化, 列变化}
        // 0:左上, 1:右上, 2:右下, 3:左下
        int directions[4][2] = {{-1, -1}, {-1, 1}, {1, 1}, {1, -1}};

        // 1. 找到每一个'1'作为起点
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) {
                if (grid[r][c] != 1) {
                    continue;
                }

                // 2. 从这个'1'开始，尝试4个初始方向
                for (int i = 0; i < 4; ++i) {
                    int dr1 = directions[i][0];
                    int dc1 = directions[i][1];

                    // --- 阶段A: 走直线 ---
                    int path1_len = 1;
                    int curr_r = r;
                    int curr_c = c;
                    bool is_two_next = true; // 1后面期望是2

                    while (true) {
                        int next_r = curr_r + dr1;
                        int next_c = curr_c + dc1;
                        int expected_val = is_two_next ? 2 : 0;

                        // 检查下一步是否合法
                        if (next_r >= 0 && next_r < n && next_c >= 0 && next_c < m && grid[next_r][next_c] == expected_val) {
                            // 合法，直路长度增加
                            path1_len++;
                            max_len = max(max_len, path1_len);

                            // --- 阶段B: 在当前点尝试转弯 ---
                            // 顺时针90度转弯: (dr, dc) -> (dc, -dr)
                            int dr2 = dc1;
                            int dc2 = -dr1;
                            
                            int path2_len = 0;
                            int turn_r = next_r;
                            int turn_c = next_c;
                            bool is_two_next_turn = !is_two_next; // 直路下一步是0，转弯后就该是2

                            while (true) {
                                int next_turn_r = turn_r + dr2;
                                int next_turn_c = turn_c + dc2;
                                int expected_val_turn = is_two_next_turn ? 2 : 0;

                                if (next_turn_r >= 0 && next_turn_r < n && next_turn_c >= 0 && next_turn_c < m && grid[next_turn_r][next_turn_c] == expected_val_turn) {
                                    path2_len++;
                                    // V形总长度 = 直路长度 + 转弯路长度
                                    max_len = max(max_len, path1_len + path2_len);
                                    
                                    // 为转弯后的下一步做准备
                                    turn_r = next_turn_r;
                                    turn_c = next_turn_c;
                                    is_two_next_turn = !is_two_next_turn;
                                } else {
                                    break; // 转弯路径中断
                                }
                            }
                            
                            // 为直路的下一步做准备
                            curr_r = next_r;
                            curr_c = next_c;
                            is_two_next = !is_two_next;
                        } else {
                            break; // 直路中断
                        }
                    }
                }
            }
        }
        return max_len;
    }

    void init_grid()
    {
        string input;
        getline(cin,input);
        vector<int> line;
        string num;

        for(auto chunk : input)
        {
            if(isdigit(chunk)) num+=chunk;
            if(chunk == ',' && !num.empty())
            {
                line.push_back(stoi(num));
                num.clear();
            }
            if(chunk == ']' && !line.empty())
            {
                line.push_back(stoi(num));
                num.clear();

                grid.push_back(line);
                line.clear();
            }
        }
    }
};