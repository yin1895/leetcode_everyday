#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// 定义事件结构体
struct Event {
    long long x;
    int delta_slope;
    
    // 按坐标排序
    bool operator<(const Event& other) const {
        return x < other.x;
    }
};

class Solution {
private:
    int n;
    int S;
    vector<pair<long long, long long>> people; // {Vi, Hi}

public:
    void init(int num, int min_dist) {
        n = num;
        S = min_dist;
    }

    void add_person(long long h, long long v) {
        people.push_back({v, h});
    }

    // 计算单个位置的总成本，用于初始化
    long long calculate_cost_at(long long position) {
        long long sum = 0;
        for (const auto& p : people) {
            long long vi = p.first;
            long long hi = abs(p.second);
            
            // 修正后的逻辑
            long long dist_x = abs(vi - position);
            long long dist_y = hi;
            
            long long cost_straight = min(dist_x, dist_y);
            long long max_side = max(dist_x, dist_y);
            
            if (max_side >= S) {
                sum += cost_straight;
            } else {
                sum += cost_straight + (S - max_side);
            }
        }
        return sum;
    }

    long long solve() {
        vector<Event> events;
        
        // 1. 生成所有斜率变化事件
        for (const auto& p : people) {
            long long vi = p.first;
            long long hi = abs(p.second);
            
            if (hi >= S) {
                // 情况 A: |Hi| >= S
                events.push_back({vi - hi, -1});
                events.push_back({vi,      2});
                events.push_back({vi + hi, -1});
            } else {
                // 情况 B: |Hi| < S
                events.push_back({vi - S,  1});
                events.push_back({vi - hi, -2});
                events.push_back({vi,      2});
                events.push_back({vi + hi, -2});
                events.push_back({vi + S,  1});
            }
        }

        // 2. 排序事件
        sort(events.begin(), events.end());

        // 3. 扫描线过程
        // 先计算第一个事件点的确切 cost
        long long current_x = events[0].x;
        long long current_cost = calculate_cost_at(current_x);
        long long min_cost = current_cost;
        
        long long current_slope = 0;
        
        // 遍历所有事件
        for (int i = 0; i < events.size(); ++i) {
            // 将 current_x 移动到当前事件的位置
            long long next_x = events[i].x;
            long long dist = next_x - current_x;
            
            // 更新 cost：新cost = 旧cost + 斜率 * 距离
            current_cost += current_slope * dist;
            min_cost = min(min_cost, current_cost); // 记录最小值
            
            // 更新当前位置和斜率
            current_x = next_x;
            current_slope += events[i].delta_slope;
        }

        return min_cost;
    }
};

int main() {
    // 优化 I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, S;
    if (cin >> n >> S) {
        Solution solver;
        solver.init(n, S);
        for (int i = 0; i < n; ++i) {
            long long h, v;
            cin >> h >> v;
            solver.add_person(h, v);
        }
        cout << solver.solve() << endl;
    }
    return 0;
}