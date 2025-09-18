#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int peopleAwareOfSecret(int n, int delay, int forget) {
        const int MOD = 1e9 + 7;

        vector<long long> dp(n + 1);  // dp[i] = 第 i 天新增知道秘密的人数
        dp[1] = 1;  // 第 1 天，只有 1 个人知道

        long long share = 0;  // 表示今天能分享秘密的人数
        for (int day = 2; day <= n; ++day) {
            // 进入分享期的人（day-delay）
            if (day - delay >= 1) {
                share = (share + dp[day - delay]) % MOD;
            }
            // 忘记秘密的人（day-forget）
            if (day - forget >= 1) {
                share = (share - dp[day - forget] + MOD) % MOD;
            }
            // 今天新增知道秘密的人数 = share
            dp[day] = share;
        }

        // 答案 = 最后 forget 天内的人数之和（还没忘记的）
        long long ans = 0;
        for (int i = n - forget + 1; i <= n; ++i) {
            if (i >= 1) ans = (ans + dp[i]) % MOD;
        }
        return (int)ans;
    }
};
