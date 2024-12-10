#include <iostream>
#include <unordered_map>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::unordered_map<int, int> value_idx;
    int n = 0, k = 0;
    std::cin >> n >> k;
    bool flag = true;
    for (int i = 1; flag && i <= n; i += 1) {
        int value = 0;
        std::cin >> value;
        if (value_idx[value] && i - value_idx[value] <= k) {
            flag = false;
        }
        value_idx[value] = i;
    }

    if (flag) {
        std::cout << "NO";
    } else {
        std::cout << "YES";
    }

    return 0;
}