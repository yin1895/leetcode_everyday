#include<iostream>
#include<vector>

using namespace std;

bool isSushu(int n)
{
    if (n == 1)
    {
        return false;
    }
    for(int i = 2;i<n;i++)
    {
        if(n%i==0)
        {
            return false;
        }
    }
    return true;
}

class Gedebahe{
    private:
        vector<int> To_divide_num;
        vector<vector<int>> result;

    public:
        Gedebahe(int n)
        {
            for(int i = 4;i<=n;i+=2)
            {
                To_divide_num.push_back(i);
                vector<int> temp;
                for(int j = 2;j<=i/2;j++)
                {
                    if(isSushu(j) && isSushu(i-j))
                    {
                        temp.push_back(j);
                        temp.push_back(i-j);
                        result.push_back(temp);
                        temp.clear();
                        break;
                    }
                }
            }

        }

        void print()
        {
            if(result.size()!=To_divide_num.size())
            {
                cout<<"Error!"<<endl;
                return;
            }
            else{
                for(int j = 0; j < result.size();j++)
                {
                    cout << To_divide_num[j] <<"="<<result[j][0]<<"+"<<result[j][1]<<endl;
                }
            }
        }
};

int main()
{
    int n= 0;
    cin >> n;
    Gedebahe demo(n);
    demo.print();
    return 0;
}

