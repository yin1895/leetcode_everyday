#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    int numOfSubarrays(vector<int>& arr, int k, int threshold) {
        double avg = 0;
        for(int i = 0;i < k;++i){
            avg += arr[i];
        }
        double base_line = threshold * k;
        int cnt = avg >= base_line ? 1: 0;

        for(int i = k;i < arr.size() ;++i){
            avg+=arr[i];
            avg-=arr[i-k];
            cnt = avg >= base_line ? cnt+1 : cnt;
        }
        return cnt;
    }
};