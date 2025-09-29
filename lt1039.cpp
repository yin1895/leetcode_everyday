#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <map>
#include <utility> // for std::pair

using namespace std;

/**
 * @class Node
 * @brief 代表多边形的一个顶点（节点）。
 */
class Node {
private:
    int value;
    Node* next;

public:
    Node(int value) : value(value), next(nullptr) {}

    int getNodeValue() { return this->value; }
    Node* getNext() { return this->next; }
    void setNextNode(Node* toConnect) { this->next = toConnect; }
};

/**
 * @class Chain
 * @brief 使用链表来表示一个环形的多边形顶点结构。
 */
class Chain {
private:
    Node* head;

public:
    Chain(const vector<int>& values) {
        if (values.empty()) {
            head = nullptr;
            return;
        }
        head = new Node(values[0]);
        Node* currentNode = head;
        for (size_t i = 1; i < values.size(); ++i) {
            Node* newNode = new Node(values[i]);
            currentNode->setNextNode(newNode);
            currentNode = newNode;
        }
        currentNode->setNextNode(head);
    }

    ~Chain() {
        if (!head) return;
        Node* currentNode = head;
        Node* tail = nullptr;
        // 找到尾部并断开环，使其变为普通链表，方便遍历删除
        while(currentNode->getNext() != head) {
            currentNode = currentNode->getNext();
        }
        tail = currentNode;
        tail->setNextNode(nullptr); 

        // 遍历并删除所有节点
        currentNode = head;
        while(currentNode != nullptr) {
            Node* toDelete = currentNode;
            currentNode = currentNode->getNext();
            delete toDelete;
        }
    }

    Node* getHead() { return this->head; }
};


/**
 * @class Solution
 * @brief 使用带记忆化的递归（自顶向下的动态规划）来解决问题。
 */
class Solution {
private:
    // 记忆化缓存，用于存储已经计算过的子问题的结果，避免重复计算。
    // key 是一个 pair<int, int> 代表子多边形的起始和结束索引 (i, j)。
    // value 是该子问题的最低得分。
    map<pair<int, int>, int> memo;

    /**
     * @brief 递归核心函数，解决子问题：计算从索引 i 到 j 的多边形的最低剖分得分。
     * @param values 顶点值的数组
     * @param i 起始顶点索引
     * @param j 结束顶点索引
     * @return 最低得分
     */
    int solve(vector<int>& values, int i, int j) {
        // 基本情况 (Base Case):
        // 如果顶点数少于3 (即一条线或一个点)，无法形成三角形，得分为0。
        if (j < i + 2) {
            return 0;
        }

        // 记忆化检查 (Memoization Check):
        // 如果这个子问题 (i, j) 之前已经计算过，直接从缓存返回结果。
        if (memo.count({i, j})) {
            return memo.at({i, j});
        }

        // 递归步骤 (Recursive Step):
        int min_score = INT_MAX;

        // 固定边 (i, j)，遍历所有可能的中间顶点 k 来形成三角形 (i, k, j)。
        // 这个三角形将原问题分割为两个更小的子问题：(i, k) 和 (k, j)。
        for (int k = i + 1; k < j; ++k) {
            int current_score = solve(values, i, k) + 
                                solve(values, k, j) + 
                                values[i] * values[k] * values[j];
            
            min_score = min(min_score, current_score);
        }

        // 将计算结果存入缓存，然后返回。
        return memo[{i, j}] = min_score;
    }

public:
    /**
     * @brief 主函数，用于启动三角剖分的计算。
     * @param values 代表多边形顶点的整数向量。
     * @return 多边形三角剖分的最低得分。
     */
    int minScoreTriangulation(vector<int>& values) {
        // 清空缓存，以防同一个 Solution 对象被用于多个不同的测试用例。
        memo.clear();
        
        // 启动递归，解决整个多边形 (从索引 0 到 n-1) 的问题。
        return solve(values, 0, values.size() - 1);
    }
};