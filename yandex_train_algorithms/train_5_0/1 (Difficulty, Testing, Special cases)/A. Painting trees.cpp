#include <iostream>

int main() {
    int p = 0, v = 0, q = 0, m = 0;
    std::cin >> p >> v >> q >> m;
    v = std::abs(v);
    m = std::abs(m);
    int min_pos = std::min(p, q);
    int max_pos = std::max(p, q);
    int min_step = 0, max_step = 0;
    int ans = 0;
    if (min_pos == p) {
        min_step = v;
        max_step = m;
    } else {
        min_step = m;
        max_step = v;
    }
    if (min_pos + min_step >= max_pos - max_step) {
        ans = std::max(std::max(min_step * 2 + 1, max_step * 2 + 1), max_pos + max_step - (min_pos - min_step) + 1);
    } else {
        ans = max_step * 2 + min_step * 2 + 2;
    }
    std::cout << ans;
    return 0;
}
