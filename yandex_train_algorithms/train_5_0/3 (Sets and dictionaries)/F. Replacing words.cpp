#include <iostream>
#include <set>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::string dictionary, words;
    std::getline(std::cin, dictionary);
    std::getline(std::cin, words);

    std::set<std::string> dict;
    std::string cur_str;

    for (char sym : dictionary) {
        if (sym == ' ') {
            dict.insert(cur_str);
            cur_str.clear();
        } else if (sym != '\n') {
            cur_str.push_back(sym);
        }
    }
    if (!cur_str.empty()) {
        dict.insert(cur_str);
    }

    cur_str.clear();
    bool flag = true;

    for (char sym : words) {
        if (flag && dict.find(cur_str) != dict.end()) {
            flag = false;
            std::cout << cur_str << ' ';
            cur_str.clear();
        }
        if (sym == ' ') {
            if (!flag) {
                flag = true;
            } else {
                std::cout << cur_str << ' ';
            }
            cur_str.clear();
        } else if (flag) {
            cur_str.push_back(sym);
        }
    }
    if (!cur_str.empty()) {
        std::cout << cur_str;
    }

    return 0;
}