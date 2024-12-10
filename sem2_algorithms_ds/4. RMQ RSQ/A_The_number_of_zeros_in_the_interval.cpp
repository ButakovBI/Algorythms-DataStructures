#include <iostream>
#include <vector>

int main() {

    size_t n = 0;
    std::cin >> n;
    std::vector<size_t> vec(n + 1);
    for (size_t i = 1; i < n + 1; i += 1) {
        int32_t a = 0;
        std::cin >> a;
        if (a == 0) {
            vec[i] = vec[i - 1] + 1;
        }
        else {
            vec[i] = vec[i - 1];
        }
    }
    size_t k = 0;
    std::cin >> k;
    std::vector<size_t> ans(k);
    for (size_t i = 0; i < k; i += 1) {
        size_t left = 0, right = 0;
        std::cin >> left >> right;
        ans[i] = vec[right] - vec[left - 1];
    }
    for (auto& elem : ans) {
        std::cout << elem << ' ';
    }
}