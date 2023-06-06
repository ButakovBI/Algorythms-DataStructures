#include <iostream>
#include <vector>

int main()
{
    int n = 0;
    std::cin >> n;
    std::vector<int> costs(n + 1);
    for (int i = 1; i <= n; i += 1) {
        std::cin >> costs[i];
    }

    std::vector<int> dp(n + 1);
    dp[1] = costs[1];
    dp[2] = costs[2];

    for (int i = 3; i <= n; i += 1) {
        dp[i] = std::min(dp[i - 1], dp[i - 2]) + costs[i];
    }
    std::cout << dp[n];
}
