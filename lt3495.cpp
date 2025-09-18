#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    long long minOperations(vector<vector<int>>& queries) {
        long long totalAns = 0;
        for (auto &q : queries) {
            long long L = q[0], R = q[1];
            if (R < 1) continue;            
            if (L < 1) L = 1;

            long long sumH = 0;            // S = 总高度
            long long maxH = 0;            // H = 最大高度
            unsigned long long p = 1;      // p = 4^{k-1}
            int k = 1;

            while (p <= (unsigned long long)R) {
                unsigned long long start = max((unsigned long long)L, p);
                unsigned long long next = p * 4ULL;   // 4^k
                unsigned long long end = min((unsigned long long)R, next - 1ULL);

                if (start <= end) {
                    unsigned long long cnt = end - start + 1ULL;
                    sumH += (long long)cnt * (long long)k;
                    maxH = max(maxH, (long long)k);
                }

                // 防止溢出
                if (p > (unsigned long long)R / 4ULL) break;
                p *= 4ULL;
                ++k;
            }

            long long ops = max(maxH, (sumH + 1) / 2); //ceil也可以
            totalAns += ops;
        }
        return totalAns;
    }
};
