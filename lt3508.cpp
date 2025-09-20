#include <bits/stdc++.h>
using namespace std;

class Packet {
public:
    int source, destination, timestamp;
    Packet(int s, int d, int t): source(s), destination(d), timestamp(t) {}
    bool operator==(const Packet &tmp) const {
        return source == tmp.source && destination == tmp.destination && timestamp == tmp.timestamp;
    }
};

class Router {
private:
    unordered_map<int, deque<Packet>> memo;        // timestamp -> 包列表
    queue<Packet> fifo;                            // 全局 FIFO
    unordered_map<int, vector<int>> destMap;       // dest -> timestamps (插入顺序)
    unordered_map<int, vector<int>> removedMap;    // dest -> 已删除 timestamps
    int memoSize, currentSize;

public:
    Router(int memoryLimit) {
        memoSize = memoryLimit;
        currentSize = 0;
    }

    bool addPacket(int source, int destination, int timestamp) {
        Packet tmp(source, destination, timestamp);

        // 去重
        for (auto &pkg : memo[timestamp]) if (pkg == tmp) return false;

        // 淘汰最早
        if (currentSize == memoSize) forwardPacket();

        memo[timestamp].push_back(tmp);
        fifo.push(tmp);
        destMap[destination].push_back(timestamp);
        currentSize++;
        return true;
    }

    vector<int> forwardPacket() {
        if (fifo.empty()) return {};
        Packet pkt = fifo.front(); fifo.pop();

        // 从桶里删除
        auto &dq = memo[pkt.timestamp];
        for (auto it = dq.begin(); it != dq.end(); ++it) {
            if (*it == pkt) { dq.erase(it); break; }
        }
        if (dq.empty()) memo.erase(pkt.timestamp);

        // 延迟删除：只记录下来(lazy delete)
        removedMap[pkt.destination].push_back(pkt.timestamp);

        currentSize--;
        return {pkt.source, pkt.destination, pkt.timestamp};
    }

    int getCount(int destination, int startTime, int endTime) {
        if (!destMap.count(destination)) return 0;

        auto &all = destMap[destination];
        auto &rm = removedMap[destination];

        // 全部包数量
        auto l = lower_bound(all.begin(), all.end(), startTime);
        auto r = upper_bound(all.begin(), all.end(), endTime);
        int total = r - l;

        // 已删除数量
        auto l2 = lower_bound(rm.begin(), rm.end(), startTime);
        auto r2 = upper_bound(rm.begin(), rm.end(), endTime);
        int removed = r2 - l2;

        return total - removed;
    }
};
