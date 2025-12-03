#include <iostream>
#include <string>
#include <vector>

class RabinKarp {
public:
    int search(const std::string& text, const std::string& pattern);
private:
    const int d = 256;
    const int q = 101; 
};

int RabinKarp::search(const std::string& text, const std::string& pattern) {
    int N = text.length();
    int M = pattern.length();
    if (M == 0) return 0;
    if (N < M) return -1;
    int pattern_hash = 0, text_hash = 0, h = 1;

    for (int i = 0; i < M - 1; ++i) {
        h = (h * d) % q;
    }

    for (int i = 0; i < M; ++i) {
        pattern_hash = (d * pattern_hash + pattern[i]) % q;
        text_hash = (d * text_hash + text[i]) % q;
    }

    for (int i = 0; i <= N - M; ++i) {
        if (pattern_hash == text_hash) {
            bool match = true;
            for (int j = 0; j < M; ++j) {
                if (text[i + j] != pattern[j]) {
                    match = false;
                    break;
                }
            }
            if (match) return i;
        }

        if (i < N - M) {
            // C++的取模运算对负数结果是实现定义的，下面这种写法更安全
            text_hash = (d * (text_hash - text[i] * h) + text[i + M]) % q;
            if (text_hash < 0) {
                text_hash += q;
            }
        }
    }
    return -1;
}

// --- 主函数，用于测试 ---
int main() {
    RabinKarp rk_solver;

    std::string text = "AABAACAADAABAABA";
    std::string pattern = "AABA";
    int index = rk_solver.search(text, pattern);
    std::cout << "模式串 '" << pattern << "' 在文本串 '" << text << "' 中首次出现的位置是: " << index << std::endl;

    std::string text2 = "ABACADABRAC";
    std::string pattern2 = "ABRAC";
    index = rk_solver.search(text2, pattern2);
    std::cout << "模式串 '" << pattern2 << "' 在文本串 '" << text2 << "' 中首次出现的位置是: " << index << std::endl;
    
    std::string text3 = "AAAAAAAAAAAAAAAAAB";
    std::string pattern3 = "AAAAAAAAB";
    index = rk_solver.search(text3, pattern3);
    std::cout << "模式串 '" << pattern3 << "' 在文本串 '" << text3 << "' 中首次出现的位置是: " << index << std::endl;

    return 0;
}