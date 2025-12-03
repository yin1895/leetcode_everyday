#include<bits/stdc++.h>

using namespace std;

class Solution {
private:
    vector<vector<int>> triangle;
    vector<vector<int>> memo; 
public:
    int minimumTotal(vector<vector<int>> input) {
        triangle = input;
        int n = triangle.size();
        memo.assign(n, vector<int>(n, INT_MAX));
        return getResult(0, 0);
        
    }

     int getResult(int i, int j) {
        if (i == triangle.size()-1) return triangle[i][j]; // 底层
        if (memo[i][j] != INT_MAX) return memo[i][j];       // 已计算过

        int left = getResult(i+1, j);
        int right = getResult(i+1, j+1);

        return memo[i][j] = triangle[i][j] + min(left, right);
    }
};