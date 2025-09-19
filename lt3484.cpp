#include<bits/stdc++.h>

using namespace std;

class Spreadsheet {
private:
    unordered_map<string,unordered_map<int,int>> table;

public:
    Spreadsheet(int rows) {
        for(char c = 'A';c<='Z';c++)
        {
            string col(1,c);
            table[col];
        }
    }
    
    void setCell(string cell, int value) {
        string col(1,cell[0]);
        cell.erase(cell.begin(),cell.begin()+1);
        int row = stoi(cell);

        table[col][row] = value;

    }
    
    void resetCell(string cell) {
        string col(1,cell[0]);
        cell.erase(cell.begin(),cell.begin()+1);
        int row = stoi(cell);

        table[col][row] = 0;
    }
    
    int getValue(string formula) {
        //init_string
        formula.erase(formula.begin());
        string st1,st2;
        auto pos = formula.find('+');
        st1 = formula.substr(0, pos);
        st2 = formula.substr(pos+1);
        
        auto getItem = [this](string tmp)
        {
            if(isdigit(tmp[0])) return stoi(tmp);
            else
            {
                string col(1,tmp[0]);
                tmp.erase(tmp.begin(),tmp.begin()+1);
                int row = stoi(tmp);

                return this->table[col].count(row)?table[col][row]:0;
            }
        };

        return getItem(st1)+getItem(st2);
    }
};