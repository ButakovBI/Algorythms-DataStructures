#include <iostream>
#include <vector>

int main() {

    int n = 0, m = 0;
    std::cin >> n >> m;

    std::vector<int> weights(n + 1);
    std::vector<int> costs(n + 1);

    for (int i = 1; i <= n; i += 1) {
        std::cin >> weights[i];
    }

    for (int i = 1; i <= n; i += 1) {
        std::cin >> costs[i];
    }

    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1));
    for (int i = 1; i <= n; i += 1) {
        int weight = weights[i];
        if (weight <= m) {
            dp[i][weight] = costs[i];
        }
        for (int j = 1; j <= m; j += 1) {
            dp[i][j] = std::max(dp[i][j], dp[i - 1][j]);
            if (weight + j <= m && dp[i - 1][j] != 0) {
                dp[i][weight + j] = std::max(dp[i][weight + j], dp[i - 1][j] + costs[i]);
            }
        }

    }

    int ans = -100001;
    for (int i = 1; i <= m; i += 1) {
        if (dp[n][i] >= ans) {
            ans = dp[n][i];
        }
    }
    std::cout << ans;
}