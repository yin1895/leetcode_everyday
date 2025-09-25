#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int bx, by, cx, cy;
    if (!(cin >> bx >> by >> cx >> cy)) return 0;

    // 标记被马占据与控制的格子
    vector<vector<bool>> blocked(bx + 1, vector<bool>(by + 1, false));
    auto mark = [&](int x, int y){
        if (0 <= x && x <= bx && 0 <= y && y <= by) blocked[x][y] = true;
    };
    mark(cx, cy);
    int dx[8] = {-2,-1, 1, 2, 2, 1,-1,-2};
    int dy[8] = { 1, 2, 2, 1,-1,-2,-2,-1};
    for (int k = 0; k < 8; ++k) mark(cx + dx[k], cy + dy[k]);

    // DP：dp[i][j] = 来自左边 + 来自下边
    vector<vector<long long>> dp(bx + 1, vector<long long>(by + 1, 0));
    if (!blocked[0][0]) dp[0][0] = 1;  // 起点可达

    for (int i = 0; i <= bx; ++i) {
        for (int j = 0; j <= by; ++j) {
            if (blocked[i][j]) continue;
            if (i == 0 && j == 0) continue;
            long long fromLeft  = (i > 0 ? dp[i - 1][j] : 0);
            long long fromDown  = (j > 0 ? dp[i][j - 1] : 0);
            dp[i][j] = fromLeft + fromDown;
        }
    }

    cout << dp[bx][by] << "\n";
    return 0;
}
