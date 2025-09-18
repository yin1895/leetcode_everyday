#include<bits/stdc++.h>

using namespace std;

class Solution{
    private:
        int n;
        long long ans;
        map<pair<int,int>,long long> memo;
    public:
        long long dfs(int prev,int curt)
        {
            if(curt==0) return 1;

            auto key = make_pair(prev,curt);
            if(memo.count(key)) return memo[key];

            long long res = 0;
            res+= dfs(prev,curt-1);
            if(prev > 0&&curt > 0) res += dfs(prev/2,curt/2);

            return memo[key] = res;
        }

        Solution()
        {
            cin >> n;
            ans = dfs(n,n/2);
            cout << ans;
        }
};

int main()
{
    Solution question;
    return 0;
}