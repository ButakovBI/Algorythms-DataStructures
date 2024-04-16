#include <iostream>
#include <vector>

int main() {
    int n = 0;
    std::cin >> n;

    std::vector<int> balls(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> balls[i];
    }

    int cur_color = balls[0];
    int cnt = 1, ans = 0;
    int idx = 1, start = 0;

    while (idx < n) {
        std::cout << idx << ' ' << cnt << ' ' << n << '\n';
        if (balls[idx] == cur_color) {
            cnt++;
            if (cnt == 3) {
                while (idx < n && balls[idx] == cur_color) {
                    idx++;
                    cnt++;
                }
                if (idx < n) {
                    cnt--;
                    idx--;
                    ans += cnt;
                    balls.erase(balls.begin() + start, balls.begin() + start + cnt);
                    n -= cnt;
                    idx -= cnt;
                    start = idx;
                    cnt = 1;
                    cur_color = balls[idx];
                }
            }
        } else {
            cur_color = balls[idx];
            start = idx;
            cnt = 1;
        }
        idx++;
    }
    std::cout << ans;

    return 0;
}