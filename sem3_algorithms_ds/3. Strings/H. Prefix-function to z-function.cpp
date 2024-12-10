#include <iostream>
#include <vector>


int main() {
    size_t n = 0;
    std::cin >> n;
    std::vector<size_t> k(n);
    for (size_t i = 0; i < n; i++) {
        std::cin >> k[i];
    }
    std::vector<size_t> z(n, 0);
    for (size_t i = 1; i < n; ++i) {
        if (k[i]) {
            z[i - k[i] + 1] = k[i];
        }
    }
    for (size_t i = 1; i < n; ) {
        size_t j = 0, v = 0;
        for (j = 1; j < z[i] && (v = std::min(z[j], z[i] - j)) >= z[i + j] ; ++j) {
            z[i + j] = v;
        }
        i += j;
    }
    for (size_t& elem : z) {
        std::cout << elem << ' ';
    }
}