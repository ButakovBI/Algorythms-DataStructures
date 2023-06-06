#include <iostream>
#include <vector>

int main()
{
    int n = 0, m = 0;
    std::cin >> n >> m;

    std::vector<std::vector<int>> dp(n + 4, std::vector<int>(m + 4));

    dp[2][2] = 1;

    for (int i = 2; i <= n + 1; i += 1) {
        for (int j = 2; j <= m + 1; j += 1) {
            dp[i][j] += dp[i - 2][j - 1] + dp[i - 1][j - 2];
        }
    }

    std::cout << dp[n + 1][m + 1];

}
