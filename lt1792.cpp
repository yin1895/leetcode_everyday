#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    double maxAverageRatio(vector<vector<int>>& classes, int extraStudents) {
        for(int i = 0; i < extraStudents; i++) {
            if(!singleStu(classes)) {
                cout << "ERROR" << endl;
                return -1;
            }
        }
        return getPassRate(classes);
    }

    bool singleStu(vector<vector<int>>& classes) {
        int indexOfMax = -1;
        double maxIncrease = -1.0;
        double base = getPassRate(classes);

        for(int i = 0; i < classes.size(); i++) {
            auto c = classes[i];
            c[0]++; c[1]++;
            double newRate = getPassRate(classes) 
                             - (static_cast<double>(classes[i][0]) / classes[i][1])
                             + (static_cast<double>(c[0]) / c[1]);

            double increase = newRate - base;
            if(increase > maxIncrease) {
                maxIncrease = increase;
                indexOfMax = i;
            }
        }

        if(indexOfMax == -1) return false;
        classes[indexOfMax][0]++;
        classes[indexOfMax][1]++;
        return true;
    }

    double getPassRate(const vector<vector<int>>& classes) {
        double rate = 0.0;
        for(auto &room : classes) {
            rate += static_cast<double>(room[0]) / room[1];
        }
        return rate / classes.size();
    }
};
