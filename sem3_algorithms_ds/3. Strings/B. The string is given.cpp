#include <cstdint>
#include <iostream>
#include <string>
#include <vector>


int main() {
    std::string s1, s2;
    std::cin >> s1;
    std::cin >> s2;
    const size_t n1 = s1.size();
    const size_t n2 = s2.size();
    const int64_t x = 257;
    const int64_t p = 1e9 + 9;
    std::vector<int64_t> pows(n1 + 1);
    pows[0] = 1;
    for (int64_t i = 1; i < n1 + 1; i += 1) {
        pows[i] = (pows[i - 1] * x) % p;
    }
    std::vector<int64_t> hash1(n1 + 1);
    hash1[0] = 0;
    for (int64_t i = 1; i < n1 + 1; i += 1) {
        hash1[i] = (hash1[i - 1] * x + s1[i - 1]) % p;
    }

    std::vector<int64_t> hash2(n2 + 1);
    hash2[0] = 0;
    for (int64_t i = 1; i < n2 + 1; i += 1) {
        hash2[i] = (hash2[i - 1] * x + s2[i - 1]) % p;
    }

    int64_t ans = 0;
    std::vector<int64_t> indices;
    for (int64_t i = 0; i < n1 - n2 + 1; i += 1) {
        if (((hash1[i + n2] - (hash1[i] * pows[n2]) % p) + p) % p == hash2[n2]) {
            ans += 1;
            indices.push_back(i);
        }
    }
    std::cout << ans << '\n';
    for (auto& idx : indices) {
        std::cout << idx + 1 << ' ';
    }
    return 0;
}