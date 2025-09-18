#include <bits/stdc++.h>
using namespace std;

struct Task {
    int userId;
    int taskId;
    int priority;
    long long version; // 全局唯一的版本号
};


struct cmp {
    bool operator()(const Task& a, const Task& b) const {
        if (a.priority == b.priority) {
            return a.taskId < b.taskId; // id 大的优先
        }
        return a.priority < b.priority; // priority 大的优先
    }
};


class TaskManager {
private:
    priority_queue<Task, vector<Task>, cmp> pq;
    unordered_map<int, long long> latestVersion; // taskId -> 当前有效版本号
    unordered_map<int, int> curUser;             // taskId -> userId（最新）
    long long globalVer = 0;                     // 全局单调版本号计数器

    long long nextVersion() { return ++globalVer; }

public:
    // 构造时接受初始任务数组，每个 task 格式 [userId, taskId, priority]
    TaskManager(vector<vector<int>>& tasks) {
        for (auto &t : tasks) {
            if (t.size() >= 3) add(t[0], t[1], t[2]);
        }
    }

    void add(int userId, int taskId, int priority) {
        long long ver = nextVersion();
        latestVersion[taskId] = ver;
        curUser[taskId] = userId;
        pq.push(Task{userId, taskId, priority, ver});
    }

    void edit(int taskId, int newPriority) {
        auto it = latestVersion.find(taskId);
        if (it == latestVersion.end()) return; // 无此任务则忽略
        int userId = curUser[taskId];          // 保留原 userId
        long long ver = nextVersion();
        latestVersion[taskId] = ver;
        pq.push(Task{userId, taskId, newPriority, ver});
    }

    void rmv(int taskId) {
        auto it = latestVersion.find(taskId);
        if (it == latestVersion.end()) return;
        // 标记为删除：移除映射，堆中的旧条目会在 execTop 时被丢弃
        latestVersion.erase(it);
        curUser.erase(taskId);
    }

    int execTop() {
        while (!pq.empty()) {
            Task t = pq.top();
            auto it = latestVersion.find(t.taskId);
            if (it == latestVersion.end() || it->second != t.version) {
                // 已删除或不是当前版本 => 丢弃
                pq.pop();
                continue;
            }
            // 找到有效的 top：执行并从系统中移除该任务
            pq.pop();
            latestVersion.erase(t.taskId);
            curUser.erase(t.taskId);
            return t.userId;
        }
        return -1;
    }
};
