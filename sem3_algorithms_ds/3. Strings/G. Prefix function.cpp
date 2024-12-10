#include <iostream>
#include <string>
#include <vector>

int main() {
    std::string s;
    std::getline(std::cin, s);
    const size_t size = s.length();
    std::vector<size_t> ans(size + 1, 0);
    for (size_t i = 1; i < size; i += 1) {
        size_t j = ans[i - 1];
        while (j > 0 && s[j] != s[i]) {
            j = ans[j - 1];
        }
        if (s[i] == s[j]) {
            j += 1;
        }
        ans[i] = j;
    }
    for (size_t i = 0; i < size; i += 1) {
        std::cout << ans[i] << ' ';
    }
    return 0;
}
