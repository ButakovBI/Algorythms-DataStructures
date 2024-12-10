#include <iostream>

int main() {
    long long ans = 0;
    int n = 0;
    std::cin >> n;
    for (int i = 0; i < n; i += 1) {
        int cnt = 0;
        std::cin >> cnt;
        ans += std::min(cnt % 4 + cnt / 4, 4 - cnt % 4 + (cnt + 3) / 4);
    }
    std::cout << ans;
    return 0;
}