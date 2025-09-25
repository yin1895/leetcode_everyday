#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<string> spellchecker(vector<string>& wordlist, vector<string>& queries) {
        vector<string> ans;
        for(const auto& chunk : queries)
        {
            string tmp = "";
            for(const auto & toCom : wordlist)
            {
                if(chunk == toCom) {tmp = toCom;}
            }
            ans.push_back(tmp);
        }
        return ans;
    }

};
bool operator== (string &s1,string &s2)
{
    auto isVowel = [](char c)
    {return c=='a'||c=='e'||c=='i'||c=='o'||c=='u'||c=='A'||c=='E'||c=='I'||c=='O'||c=='U';};

    int tmp = 'A' - 'a';
    
    if(s1.size()!=s2.size()) return false;
    for(int i = 0;i<s1.size();i++)
    {
        if(!isVowel(s1[i])&&!isVowel(s2[i]))
        {
            if(tolower(s1[i]) != tolower(s2[i])){return false;}
        }
        else if(!isVowel(s1[i])&&isVowel(s2[i])) return false;
        else if(!isVowel(s2[i])&&isVowel(s1[i])) return false;
    }
    return true;
}