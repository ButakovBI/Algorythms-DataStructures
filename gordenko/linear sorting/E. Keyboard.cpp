#include <iostream>
#include <vector>

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<int> clicks(n);
    for (int i = 0; i < n; i += 1) {
        std::cin >> clicks[i];
    }

    int k = 0;
    std::cin >> k;
    int click_idx = 0;
    for (int i = 0; i < k; i += 1) {
        std::cin >> click_idx;
        clicks[click_idx - 1]--;
    }

    for (int i = 0; i < n; i += 1) {
        std::cout << ((clicks[i] < 0) ? "yes" : "no") << '\n';
    }

    return 0;
}
