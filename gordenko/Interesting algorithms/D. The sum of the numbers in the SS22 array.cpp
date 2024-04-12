#include <iostream>
#include <vector>

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<int> prefix(n + 1);
    prefix[0] = 0;
    int min_pos = 0, max_pos = 0, last_min = 0;
    int value = 0;
    for (int i = 1; i <= n; i++) {
        std::cin >> value;
        prefix[i] = prefix[i - 1] + value;
        if (prefix[i] <= prefix[last_min]) {
            last_min = i;
        }
        if (prefix[max_pos] - prefix[min_pos] < prefix[i] - prefix[last_min]) {
            min_pos = last_min;
            max_pos = i;
        }
    }
    if (max_pos > min_pos) {
        std::cout << min_pos << ' ' << max_pos - 1;
    } else {
        std::cout << 0 << ' ' << 0;
    }

    return 0;
}