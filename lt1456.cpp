#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    int maxVowels(string s, int k) {
        auto isVowel = [](char c){ return c=='a'||c=='e'||c=='i'||c=='o'||c=='u';};

        int n = s.size();
        int cnt = 0;

        for(int i = 0;i<k ;i++)
        {
            if(isVowel(s[i])) cnt++;
        }
        int ans = cnt;

        for(int i = k;i<n ;i++)
        {
            if(isVowel(s[i])) cnt ++;
            if(isVowel(s[i-k])) cnt --;

            ans = max(ans,cnt);
        }

        return ans;
    }
};