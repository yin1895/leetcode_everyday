#include<bits/stdc++.h>

using namespace std;

class Solution {
private:
    priority_queue<int, vector<int>,greater<int>> pq;

public:
    Solution()= default;

    void caseFor1(int inputValue){
        pq.push(inputValue);
    }

    bool caseFor2(int &out){
        if(pq.empty()) return false;

        out= pq.top();
        return true;
    }

    bool caseFor3() {
        if(pq.empty()) return false;
        pq.pop();
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if(!(cin >> n)) return 0;
    string line;
    getline(cin, line);

    Solution solve;
    for(int i = 0;i < n;++i){
        if(!getline(cin,line)) break;

        if(line.empty()){--i;continue;}

        istringstream iss(line);
        int cmd;
        if(!(iss>>cmd)) {
            cerr << "Invalid command line" << line <<'\n';
            continue;
        }

        if(cmd == 1) {
            long long x;
            if(!(iss>>x)) {
                cerr << "Insert error" << endl;
                continue;
            }
            solve.caseFor1(x);
            }else if (cmd == 2) {
                int val;
                if (solve.caseFor2(val)) {
                    cout << val << '\n';
                } else {
                    cout << "ERROR: Empty\n";
                }
            } else if (cmd == 3) {
                if (!solve.caseFor3()) {
                    cout << "ERROR: Empty\n";
                }
            } else {
                cerr << "Unknown command: " << cmd << '\n';
            }
        }

        return 0;
}
