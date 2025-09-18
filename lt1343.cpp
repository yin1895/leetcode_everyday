#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    int numOfSubarrays(vector<int>& arr, int k, int threshold) {
        double tmp=0;
        for(int i = 0;i<k;i++) tmp+=arr[i];
        double avg = tmp/k;
        int ans = avg >= threshold ? 1 : 0;
        for(int i = k;i<arr.size();i++)
        {
            tmp-=arr[i-k];
            tmp+=arr[i];
            avg = tmp / k;
            if(avg >= threshold) ans++;
        }

        return ans;
    }
};