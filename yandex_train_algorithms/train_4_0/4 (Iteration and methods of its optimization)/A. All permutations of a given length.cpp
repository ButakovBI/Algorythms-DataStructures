#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> ans;


void permutations(std::string s, int i, int n) {
    if (i == n - 1) {
        ans.push_back(s);
        return;
    }
    for (int j = i; j < n; j += 1) {
        std::swap(s[i], s[j]);
        permutations(s, i + 1, n);
        std::swap(s[i], s[j]);
    }
}


int main() {
    int n = 0;
    std::cin >> n;
    std::string cur_str = "";
    for (int i = 1; i <= n; i += 1) {
        cur_str += std::to_string(i);
    }
    permutations(cur_str, 0, n);
    std::sort(ans.begin(), ans.end());
    for (auto& elem : ans) {
        std::cout << elem << '\n';
    }
}
