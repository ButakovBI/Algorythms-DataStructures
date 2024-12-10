#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<int> values(n);
    for (int i = 0; i < n; i += 1) {
        std::cin >> values[i];
    }
    std::sort(values.begin(), values.end());

    int m = 0;
    std::cin >> m;
    for (int i = 0; i < m; i += 1) {
        int l = 0, r = 0;
        std::cin >> l >> r;
        std::cout << std::upper_bound(values.begin(), values.end(), r) -
        std::lower_bound(values.begin(), values.end(), l) << ' ';
    }
    return 0;
}