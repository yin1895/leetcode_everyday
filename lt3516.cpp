#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    int findClosest(int x, int y, int z) {
        int xToz = x-z>0?x-z : z-x;
        int yToz = z-y>0?z-y : y-z;

        if(xToz > yToz) return 2;
        else if(yToz > xToz) return 1;
        else return 0;
    }
};