#include <iostream>
#include <vector>

int main()
{
    int n = 0;
    std::cin >> n;

    std::vector<int> dp(n + 3);

    int a1 = 0, b1 = 0, c1 = 0;
    std::cin >> a1 >> b1 >> c1;

    dp[1] = a1;
    dp[2] = b1;
    dp[3] = c1;

    for (int i = 2; i <= n; i += 1) {
        int a = 0, b = 0, c = 0;
        std::cin >> a >> b >> c;
        if (dp[i] != 0) {
            dp[i] = std::min(dp[i - 1] + a, dp[i]);
        }
        else {
            dp[i] = dp[i - 1] + a;
        }
        if (dp[i + 1] != 0) {
            dp[i + 1] = std::min(dp[i - 1] + b, dp[i + 1]);
        }
        else {
            dp[i + 1] = dp[i - 1] + b;
        }
        if (dp[i + 2] != 0) {
            dp[i + 2] = std::min(dp[i - 1] + c, dp[i + 2]);
        }
        else {
            dp[i + 2] = dp[i - 1] + c;
        }
    }

    std::cout << dp[n];
}
