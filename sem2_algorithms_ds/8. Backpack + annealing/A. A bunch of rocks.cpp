#include <iostream>
#include <vector>
#include <bitset>

int main() {
    size_t n = 0;
    int ans = 0;
    std::cin >> n;
    std::vector<int> v(n);
    for (int i = 0; i < v.size(); i += 1) {
        std::cin >> v[i];
        ans += v[i];
    }
    for (int i = 0; i < (1 << n); i += 1) {
        std::bitset<21> b = i;
        int s0 = 0, s1 = 0;
        for (size_t j = 0; j < n; j += 1) {
            if (b[j] == 0) {
                s0 += v[j];
            }
            else {
                s1 += v[j];
            }
        }
        if (ans > std::abs(s0 - s1)) {
            ans = std::abs(s0 - s1);
        }
    }
    std::cout << ans;
}