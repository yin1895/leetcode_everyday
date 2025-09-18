#include<bits/stdc++.h>

using namespace std;

class Solution{
    private:
        long long x;
        long long y;
        long long z;
        map<tuple<long long,long long,long long>,long long> memo;

    public:
        long long dfs(long long a ,long long b,long long c)
        {
            auto key = make_tuple(a,b,c);
            if(memo.count(key)) return memo[key];

            if(a<=0||b<=0||c<=0) return memo[key]=1;
            if(a>20||b>20||c>20) return memo[key]=dfs(20,20,20);
            if(a<b&&b<c) return memo[key] = dfs(a,b,c-1)+dfs(a,b-1,c-1)-dfs(a,b-1,c);

            return memo[key] = dfs(a-1,b,c) + dfs(a-1,b-1,c) + dfs(a-1,b,c-1) - dfs(a-1,b-1,c-1);
        }

        Solution(long long a,long long b,long long c):x(a),y(b),z(c)
        {
            cout << "w("<<x<<", "<<y<<", "<<z<<") = "<<dfs(x,y,z)<<endl;;
        }
};

int main()
{
    long long a=0;
    long long b=0;
    long long c=0;
    while(cin >> a >> b >> c) {
        if(a==-1 && b==-1 && c==-1) break;
        Solution tmp(a,b,c);
    }
    return 0;
}