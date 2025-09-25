//leetcode 498对角线遍历
#include<iostream>
#include<vector>
#include<string>
#include<cctype>

using namespace std;

class Solution{
    private:
        vector<vector<int>> mat;
        int m;
        int n;

    public:
        Solution()
        {
            m = n = 0;
            init_mat();
        }

        vector<int> findDiagonalOrder(){
            int m = mat.size();
            int n = mat.empty() ? 0 : mat[0].size();
            vector<int> ans;
            for(int i = 0; i<m+n-1;i++)
            {
                if(i%2==0)
                {
                    for(int j = i;j>=0;j--)
                    {
                        if(j<m && i-j>=0 && i-j < n) ans.push_back(mat[j][i-j]);
                    }
                }
                else{
                    for(int k = 0;k<=i;k++)
                    {
                        if(k<m && i-k>=0 && i-k < n) ans.push_back(mat[k][i-k]);
                    }
                }
            }
            return ans;
        }

        void init_mat() 
    {
        string input;
        getline(cin, input);
        string single_nums;
        vector<int> tmp_line;

        for (char chunk : input) {
            if (isdigit(chunk) || chunk == '-') {
                single_nums += chunk;
            } else if (chunk == ',') {
                if (!single_nums.empty()) {
                    tmp_line.push_back(stoi(single_nums));
                    single_nums.clear();
                }
            } else if (chunk == ']') {
                if (!single_nums.empty()) {
                    tmp_line.push_back(stoi(single_nums));
                    single_nums.clear();
                }
                if (!tmp_line.empty()) {
                    mat.push_back(tmp_line);
                    tmp_line.clear();
                }
            }
        }

        m = mat.size();
        n = mat.empty() ? 0 : mat[0].size();
    }


        void print_mat()
        {
            for( auto line : mat)
            {
                for(auto chunk : line)
                {
                    cout << chunk << " ";
                }
                cout << endl;
            }
        }
};

int main()
{
    Solution s1;
    s1.print_mat();
    vector<int> ans = s1.findDiagonalOrder();
    for(auto chunk : ans)
    {
        cout << chunk << " ";
    }
    cout << endl;
    return 0;
}