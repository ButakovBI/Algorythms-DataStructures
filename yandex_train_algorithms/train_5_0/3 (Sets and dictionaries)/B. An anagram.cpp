#include <iostream>
#include <string>
#include <unordered_map>

int main() {
    std::string s1, s2;
    std::cin >> s1 >> s2;
    std::unordered_map<char, int> symbols;
    for (char sym : s1) {
        symbols[sym]++;
    }
    for (char sym : s2) {
        symbols[sym]--;
    }
    bool flag = true;
    for (auto& elem : symbols) {
        if (elem.second != 0) {
            flag = false;
        }
    }
    if (flag) {
        std::cout << "YES";
    } else {
        std::cout << "NO";
    }

    return 0;
}