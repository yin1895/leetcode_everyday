#include<bits/stdc++.h>

using namespace std;

class Solution{
    private:
        int input;
        int output;
        vector<long long> C;

    public:
        void pushOrPop()
        {
            C.resize(input+1,0);
            C[0]=1;
            for(int i=1;i<=input;i++){
                for(int j=0;j<i;j++){
                    C[i] += C[j]*C[i-1-j];
                    }
                }
            output = C[input];
        }

        Solution()
        {
            cin >> input;
            pushOrPop();
            cout << output << endl;
        }
};

int main()
{
    Solution question;
    return 0;
}