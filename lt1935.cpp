#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    int canBeTypedWords(string text, string brokenLetters) {
        vector<string> init_chunk;
        string tmp;
        for(const auto& chunk : text)
        {
            if( chunk != ' ') tmp+=chunk;
            else{
                if(!tmp.empty())
                {
                    init_chunk.push_back(tmp);
                    tmp.clear();
                }
            }
        }
        if (!tmp.empty()) init_chunk.push_back(tmp); 
        unordered_set<char> toDetect;
        for(const auto& chunk : brokenLetters)
        {
            toDetect.insert(chunk);
        }

        int ans = 0;
        for(const auto& line : init_chunk)
        {
            bool canInput = true;
            for(const auto& chunk : line)
            {
                if(toDetect.count(chunk)) {canInput = false;break;}
            }

            if(canInput) ans++;
        }

        return ans;
    }
};