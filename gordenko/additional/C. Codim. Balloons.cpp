#include <iostream>
#include <vector>

int main() {
    int n = 0;
    std::cin >> n;

    std::vector<int> balls(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> balls[i];
    }

    int ans = 0;
    int idx = 0;

    while (idx < n) {
        int start = idx;
        int cnt = 1;
        while (idx + 1 < n && balls[idx] == balls[idx + 1]) {
            ++idx;
            ++cnt;
        }

        if (cnt >= 3) {
            ans += cnt;
            balls.erase(balls.begin() + start, balls.begin() + idx + 1);
            n -= cnt;
            idx = 0;
        } else {
            ++idx;
        }
    }

    std::cout << ans;

    return 0;
}