#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<int> replaceNonCoprimes(vector<int>& nums) {
        vector<long long> st;
        for(int x : nums){
            st.push_back(x);
            while(st.size()>1){
                long long a = st.back();st.pop_back();
                long long b = st.back();st.pop_back();
                long long g = gcd(a,b);
                if(g>1) st.push_back(lcm(a,b));
                else{
                    st.push_back(b);
                    st.push_back(a);
                    break;
                }
            }
        }
        vector<int> ans;
        for(auto x : st) ans.push_back((int)x);

        return ans;
    }
};