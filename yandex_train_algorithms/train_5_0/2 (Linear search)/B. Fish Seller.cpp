#include <iostream>
#include <vector>

int main() {
    int n = 0, k = 0;
    std::cin >> n >> k;
    int max_money = 0;
    std::vector<int> prices(n);
    for (int i = 0; i < n; i += 1) {
        std::cin >> prices[i];
    }
    for (int i = 0; i < n; i += 1) {
        int cur_days = std::min(n, i + k + 1);
        for (int j = i + 1; j < cur_days; j += 1) {
            if (prices[j] - prices[i] > max_money) {
                max_money = prices[j] - prices[i];
            }
        }
    }
    std::cout << max_money;

    return 0;
}