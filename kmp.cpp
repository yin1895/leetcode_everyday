#include<iostream>
#include<string>
#include<vector>

using namespace std;

class KMP{
public:
    KMP(const string& pattern){
        this -> pattern = pattern;
        computeNext();
    }

    int search(const string& text);

private:
    string pattern;
    vector<int> next;

    void computeNext();
};

void KMP::computeNext() {
    int M = pattern.length();
    next.resize(M);

    int k = 0;
    
    next[0] = 0;

    for(int j = 1; j < M;++j) {
        while(k > 0 && pattern[j] != pattern[k]) {
            k = next[k-1];
        }

        if (pattern[k] == pattern[j]) {
            ++k;
        }

        next[j] = k;
    }
}

int KMP::search(const string& text) {
    int N = text.length();
    int M = pattern.length();

    if (M == 0) return 0;
    if (N < M) return -1;

    int i = 0;
    int j = 0;

    while (i < N)
    {
        if(text[i] == pattern[j]) {
            i++;
            j++;
        }

        if(j == M) {
            return i - M;
        }

        else if(i < N && text[i] != pattern[j]) {
            if (j > 0) {
                j = next[j - 1];
            } else {
                i++;
            }
        }
    }
    return -1;
}

int main() {
    std::string text = "AABAACAADAABAABA";
    std::string pattern = "AABA";

    KMP kmp_solver(pattern);
    int index = kmp_solver.search(text);

    if (index != -1) {
        std::cout << "模式串 '" << pattern << "' 在文本串 '" << text << "' 中首次出现的位置是: " << index << std::endl;
    } else {
        std::cout << "在文本串中未找到模式串。" << std::endl;
    }

    // 另一个测试
    std::string text2 = "ABACADABRAC";
    std::string pattern2 = "ABRAC";
    KMP kmp_solver2(pattern2);
    index = kmp_solver2.search(text2);
    std::cout << "模式串 '" << pattern2 << "' 在文本串 '" << text2 << "' 中首次出现的位置是: " << index << std::endl;


    return 0;
}