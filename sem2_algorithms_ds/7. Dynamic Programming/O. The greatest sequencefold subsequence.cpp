#include <iostream>
#include <vector>

int main() {

    int n = 0;
    std::cin >> n;

    std::vector<int> numbers(n + 1);

    std::vector<int> dp(n + 1, 1);

    for (int i = 1; i <= n; i += 1) {
        std::cin >> numbers[i];
    }

    for (int i = 1; i <= n; i += 1) {
        for (int j = 1; j < i; j += 1) {
            if (numbers[i] % numbers[j] == 0) {
                dp[i] = std::max(dp[j] + 1, dp[i]);
            }
        }
    }

    int ans = 1;

    for (auto& elem : dp) {
        if (elem > ans) {
            ans = elem;
        }
    }
    std::cout << ans;
}
