// #include<bits/stdc++.h>

// using namespace std;

// class NumberContainers {
// private:
//     unordered_map<int,int> keyToValue;
//     unordered_map<int,vector<int>> memoOfValue;
// public:
//     NumberContainers() {
//     }
    
//     void change(int index, int number) {
//         if(keyToValue.count(index))
//         {
//             auto& vec = memoOfValue[keyToValue[index]];
//             auto it = std::find(vec.begin(), vec.end(), index);
//             if (it != vec.end()) {
//                 vec.erase(it);
//             }//删除被覆盖值的键组里这个键避免冲突
//             memoOfValue[number].push_back(index);
//             //添加新值键组
//             keyToValue[index] = number;
//         }
//         else{
//             keyToValue[index] = number;
//             memoOfValue[number].push_back(index);
//         }
//     }
    
//     int find(int number) {
//         auto &vec = memoOfValue[number];
//         if(vec.empty()) return -1;
//         sort(vec.begin(),vec.end());
//         return *vec.begin();
//     }
// };

#include <bits/stdc++.h>
using namespace std;

class NumberContainers {
private:
    unordered_map<int,int> keyToValue;        // index -> number
    unordered_map<int,set<int>> valueToKeys;  // number -> sorted indices
    
public:
    NumberContainers() {}

    void change(int index, int number) {
        if(keyToValue.count(index)) {
            int oldValue = keyToValue[index];
            valueToKeys[oldValue].erase(index); // O(log n)
        }
        keyToValue[index] = number;
        valueToKeys[number].insert(index); // O(log n)
    }

    int find(int number) {
        if(valueToKeys.count(number) && !valueToKeys[number].empty()) {
            return *valueToKeys[number].begin(); // O(1)，取最小
        }
        return -1;
    }
};
