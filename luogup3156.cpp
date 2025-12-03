#include<bits/stdc++.h>
using namespace std;

int main(){
    int n, m;
    cin >> n >> m;
    vector<int> nums;
    for(int i = 0;i < n; ++i){
        int tmp = 0;
        cin >> tmp;
        nums.push_back(tmp);
    }

    vector<int> index;
    for(int i = 0;i < m;++i){
        int tmp = 0;
        cin >> tmp;
        index.push_back(tmp);
    }

    for(const auto it : index) {
        cout << nums[it - 1] << endl;
    }

    return 0;
}