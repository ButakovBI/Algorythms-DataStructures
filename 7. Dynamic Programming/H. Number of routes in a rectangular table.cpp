#include <iostream>
#include <vector>

int main()
{
    int n = 0, m = 0;
    std::cin >> n >> m;

    std::vector<std::vector<int>> dp(n + 2, std::vector<int>(m + 2));

    for (int i = 1; i <= n; i += 1) {
        dp[i][1] = 1;
    }
    for (int i = 1; i <= m; i += 1) {
        dp[1][i] = 1;
    }

    for (int i = 2; i <= n; i += 1) {
        for (int j = 2; j <= m; j += 1) {
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        }
    }
    std::cout << dp[n][m];

}
