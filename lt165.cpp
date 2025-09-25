#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    int compareVersion(string version1, string version2) {
        vector<int> num1,num2;
        str2int(version1,num1);
        str2int(version2,num2);

        int i = 0, j = 0;
    while (i < num1.size() || j < num2.size()) {
        int x = i < num1.size() ? num1[i] : 0;
        int y = j < num2.size() ? num2[j] : 0;
        if (x < y) return -1;
        if (x > y) return 1;
        i++; j++;
    }
    return 0;

    }

    void str2int(string str,vector<int>&num)
    {
        string tmp;
        int chunk2Store;
        for(auto chr : str)
        {
            if(isdigit(chr)) tmp+=chr;
            if(chr == '.')
            {
                chunk2Store = stoi(tmp);
                num.push_back(chunk2Store);
                tmp.clear();
            }
        }

        if(!tmp.empty()){chunk2Store = stoi(tmp);num.push_back(chunk2Store);}
    }
};