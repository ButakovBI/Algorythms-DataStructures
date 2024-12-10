#include <iostream>
#include <vector>

int main()
{
    int n = 0, m = 0;
    std::cin >> n >> m;

    std::vector<std::vector<int>> costs(n + 1, std::vector<int>(m + 1));

    for (int i = 1; i <= n; i += 1) {
        for (int j = 1; j <= m; j += 1) {
            std::cin >> costs[i][j];
        }
    }

    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1));


    for (int i = 1; i <= n; i += 1) {
        for (int j = 1; j <= m; j += 1) {
            if (dp[i - 1][j] == 0) {
                dp[i][j] = costs[i][j] + dp[i][j - 1];
            }
            else if (dp[i][j - 1] == 0) {
                dp[i][j] = costs[i][j] + dp[i - 1][j];
            }
            else {
                dp[i][j] = std::min(dp[i][j - 1], dp[i - 1][j]) + costs[i][j];
            }
        }
    }
    std::cout << dp[n][m];

}
