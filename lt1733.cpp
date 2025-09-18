#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    int minimumTeachings(int n, vector<vector<int>>& languages, vector<vector<int>>& friendships) {
        int person = languages.size();

        vector<unordered_set<int>> langSet(person+1);

        for(int i = 0;i<person;i++)
        {
            for(int l : languages[i]) langSet[i+1].insert(l);
        }

        unordered_set<int> candidates;

        for(auto &relation : friendships)
        {
            int u = relation[0],v = relation[1];
            bool can = false;
            for(int l : langSet[u])
            {
                if(langSet[v].count(l)){can = 1;break;}
            }
            if(!can) {
                candidates.insert(u);
                candidates.insert(v);
            }
        }

        if(candidates.empty()) return 0;

        vector<int> cnt(n+1,0);
        for(int per : candidates)
        {
            for(int l : langSet[per]) cnt[l]++;
        }

        int maxKownLanguage = *max_element(cnt.begin(),cnt.end());

        return (int)candidates.size() - maxKownLanguage;
    }

};