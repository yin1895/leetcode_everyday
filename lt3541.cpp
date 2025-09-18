#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    int maxFreqSum(string s) {
        unordered_map<char,int> memo_Vowel;
        unordered_map<char,int> memo;

        unordered_set<char> vowels{'a', 'e', 'i', 'o', 'u'};

        for (const auto& chunk : s) {
            if (vowels.count(chunk)) {
                memo_Vowel[chunk]++;
            } else {
                memo[chunk]++;
            }
        }

        int max1=0;
        int max2=0;

        for(const auto&pair : memo_Vowel)
        {
            max1 = max(max1, pair.second);
        }

        for(const auto&pair : memo)
        {
            max2 = max(max2, pair.second);
        }

        return max1+max2;
    }
};