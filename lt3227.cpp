#include<bits/stdc++.h>

using namespace std;

// class Solution {
// private:
//     bool isAliceTurn = true;

// public:
//     bool doesAliceWin(string s,bool isAliceTurn) {
//         if(s.empty()||cntVowel(s)==0) return false;

//         for(int i = 1;i<=s.size();i+=2)
//         {
//             for(int j = 0; j<s.size()-i-1;j++)
//             {
//                 string tmp;
//                 for(int k = j;k<j+i;k++)
//                 {
//                     tmp+=s[k];
//                 }
                
//                 if((cntVowel(tmp)%2)==(isAliceTurn?1:0))
//                     {
//                         s.erase(s.begin()+j,s.end()+j+i);
//                         return doesAliceWin(s,!isAliceTurn);
//                     }
//                 else  return false;
//             }
//         }
//     }

//     int cntVowel(string&s)
//     {
//         int cnt = 0;
//         auto isVowel = [](char a){return a == 'a'||a=='e'||a=='i'||a=='o'||a=='u';};
//         for(const auto&chr : s)
//         {
//             if(isVowel(chr)) cnt++;
//         }

//         return cnt;
//     }
// };

class Solution {
public:
    bool doesAliceWin(string s) {
        auto isVowel = [](char a)
        {return a=='a'||a=='e'||a=='i'||a=='o'||a=='u';};

        int cnt =0;

        for(const auto &chr : s)
        {
            if(isVowel(chr)) cnt++;
        }
        if(cnt>0) return true;
        else return false;
    }
};