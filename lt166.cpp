#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {
        // 如果分子为0，结果直接为"0"
        if (numerator == 0) {
            return "0";
        }

        string result = "";

        // 1. 处理符号
        // 使用异或(^)判断分子分母是否异号
        if ((numerator > 0) ^ (denominator > 0)) {
            result += "-";
        }

        // 2. 将分子分母转为长整型(long long)并取绝对值，防止溢出
        // 例如，当 numerator 为 INT_MIN (-2^31) 时，abs(numerator) 会导致溢出
        long long num = abs((long long)numerator);
        long long den = abs((long long)denominator);

        // 3. 计算整数部分
        result += to_string(num / den);
        long long remainder = num % den;

        // 如果余数为0，说明可以整除，直接返回结果
        if (remainder == 0) {
            return result;
        }

        // 4. 处理小数部分
        result += ".";

        // 使用哈希表记录出现过的余数以及它在结果字符串中的位置
        unordered_map<long long, int> remainderMap;

        // 模拟长除法
        while (remainder != 0) {
            // 检查当前余数是否已经出现过
            if (remainderMap.find(remainder) != remainderMap.end()) {
                // 如果余数重复出现，说明找到了循环节
                // 在循环节的起始位置插入左括号
                result.insert(remainderMap[remainder], "(");
                // 在末尾追加右括号
                result += ")";
                // 结束循环
                break;
            }

            // 存储当前余数和它对应的小数位在字符串中的索引
            remainderMap[remainder] = result.length();

            // 余数乘以10，继续做除法
            remainder *= 10;

            // 将计算出的小数位追加到结果中
            result += to_string(remainder / den);

            // 更新余数
            remainder %= den;
        }

        return result;
    }
};