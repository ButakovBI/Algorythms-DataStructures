#include <cmath>
#include <cstdint>
#include <iostream>
#include <vector>


int main() {
    size_t n = 0;
    std::cin >> n;
    std::vector<std::vector<std::pair<size_t, int16_t>>> gr(n + 1);
    for (size_t i = 0; i < n; i += 1) {
        for (size_t j = 0; j < n; j += 1) {
            int16_t a = 0;
            std::cin >> a;
            if (a && j < i) {
                gr[i + 1].emplace_back(j + 1, a);
            }
        }
    }
    int32_t ans = 0;
    size_t ans_numbers = 0;
    for (size_t i = 1; i < std::pow(2, n) - 2; i += 2) {
        std::vector<bool> bits(n + 1, false);

        for (int idx = 0; idx < n + 1; idx += 1) {
            bits[n - idx] = (i >> idx) & 1;
        }
        int32_t cnt = 0;
        for (int idx = 1; idx < gr.size(); idx += 1) {
            for (auto& [to, w] : gr[idx]) {
                if (bits[idx] != bits[to]) {
                    cnt += w;
                }
            }
        }
        if (cnt > ans) {
            ans = cnt;
            ans_numbers = i;
        }
    }
    std::cout << ans << '\n';
    std::vector<bool> numbers(n + 1, false);

    for (int idx = 0; idx < n + 1; idx += 1) {
        numbers[n - idx] = (ans_numbers >> idx) & 1;
    }
    for (int i = 1; i < n + 1; i += 1) {
        std::cout << numbers[i] + 1 << ' ';
    }
    return 0;
}