#include<bits/stdc++.h>
using namespace std;

class Solution {
private:
    string input;
    vector<int> ans;
    vector<string> memo_str;
    vector<int> memo_index;
public:
    int maxOperations(string s) {
        update_memo(input);
        find();
        sort(ans.begin(),ans.end());
        return ans.back();
    }

    void find() {
        if(memo_index.empty() || memo_index.empty()) return;
        int single_memo = 0;
        if (modify(memo_index.back(), memo_str.back(), single_memo) ){
            ans.push_back(single_memo);
            memo_str.pop_back();
            memo_index.pop_back();
            update_memo(memo_str.back());
            find();
            memo_index.pop_back();
            memo_str.pop_back();
        }
    }

    bool modify(int index, string&todo, int& single_memo ) {
        single_memo = 0;
        if (todo[index] != '1') {
        cout<<"起点索引出错" << endl;
        return false;
        }
        else {
            int end = todo.size();
            while(index <= end) {
                if(todo[index] != '1' || index != end-1) {
                    swap(todo[index], todo[index+1]);
                    single_memo++;
                }
            }
            return true;
        }
    }

    void update_memo(string aftertodo){
        for(int i = 0; i < aftertodo.size();++i){
            if(aftertodo[i] == '1'){
                memo_index.push_back(i);
                memo_str.push_back(aftertodo);
            }
        }
    }
};