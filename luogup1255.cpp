#include <bits/stdc++.h>
using namespace std;

class BigNum {
private:
    string num; // 存数字

public:
    BigNum() { num = "0"; }
    BigNum(string input) { num = input; }

    // 设置整数
    void setInt(int n) {
        num = to_string(n);
    }

    // 大数加法
    BigNum operator+(const BigNum &tmp) const {
        vector<int> a, b, ans;

        for (auto chr : num) a.push_back(chr - '0');
        for (auto chr : tmp.num) b.push_back(chr - '0');

        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());

        int n = max(a.size(), b.size());
        ans.resize(n, 0);

        for (int i = 0; i < n; i++) {
            if (i < (int)a.size()) ans[i] += a[i];
            if (i < (int)b.size()) ans[i] += b[i];
            if (ans[i] >= 10) {
                if (i + 1 == (int)ans.size()) ans.push_back(0);
                ans[i + 1] += ans[i] / 10;
                ans[i] %= 10;
            }
        }

        reverse(ans.begin(), ans.end());
        string output;
        for (auto chr : ans) output += (chr + '0');
        return BigNum(output);
    }

    void printBigNum() {
        cout << num;
    }
};

class Solution {
private:
    int N;

public:
    void getAns() {
        cin >> N;
        vector<BigNum> dp(N + 1);
        dp[0].setInt(1);
        dp[1].setInt(1);

        for (int i = 2; i <= N; i++) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }

        dp[N].printBigNum();
    }
};

int main() {
    Solution question;
    question.getAns();
    return 0;
}
