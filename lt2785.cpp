#include<bits/stdc++.h>

using namespace std;

class Solution {

public:
    string sortVowels(string s) {
        string copy;
        copy.resize(s.size());

        vector<char> tmp;//index_to_input,index_in_s,char

        auto isVowel =  [](char c){return (c=='a'||c=='e'||c=='i'||c=='o'||c=='u'||c=='A'||c=='E'||c=='I'||c=='O'||c=='U');};

        for(int i = 0;i<s.size();++i)
        {
            if(isVowel(s[i])) {
                tmp.push_back(s[i]);
                copy[i] = '!';
            } 
            else copy[i] = s[i];
        }

        sort(tmp.begin(),tmp.end());

        int iter = 0;
        for(int i = 0;i<s.size();++i)
        {
            if(copy[i]=='!')
            {
                copy[i] = tmp[iter];
                iter++;
            }
        }

        return copy;
    }
};