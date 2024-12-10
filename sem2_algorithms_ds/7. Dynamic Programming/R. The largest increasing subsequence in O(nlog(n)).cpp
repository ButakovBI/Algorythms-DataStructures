#include <iostream>
#include <vector>
#include <algorithm>

const int inf = 1e9;

int main() {

    int n = 0;
    std::cin >> n;

    std::vector<int> numbers(n + 1);

    int a0 = 0, k = 0, b = 0, m = 0;
    std::cin >> a0 >> k >> b >> m;

    numbers[1] = a0;

    for (int i = 2; i <= n; i += 1) {
        numbers[i] = (k * numbers[i - 1] + b) % m;
    }

    std::vector<int> dp(n + 1, 1);

    for (int i = 1; i <= n; i += 1) {
        dp[i] = inf;
    }
    dp[0] = -inf;

    for (int i = 1; i <= n; i += 1) {
        int j = int(std::upper_bound(dp.begin(), dp.end(), numbers[i]) - dp.begin());
        if (dp[j - 1] < numbers[i] && numbers[i] < dp[j])
            dp[j] = numbers[i];
    }

    int ans = 0;

    for (int i = 1; i <= n; i += 1) {
        if (dp[i] != inf && dp[i] != -inf) {
            ans += 1;
        }
    }
    std::cout << ans;
}