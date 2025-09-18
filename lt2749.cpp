#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    int makeTheIntegerZero(int num1, int num2) {
        for (int k = 1; k <= 60; k++) {  // 最多 60 步
            long long x = (long long)num1 - (long long)num2 * k;
            if (x < 0) break;
            if (__builtin_popcountll(x) <= k && k <= x) return k;
        }
        return -1;
    }
};
