#include <iostream>
#include <vector>

const int MOD = 1e9 + 7;

int countWaysToAchieveWeight(int n, int m, const std::vector<int>& magicalNumbers) {
    // dp[w] will store the number of ways to get weight w
    std::vector<long long> dp(n + 1, 0);
    dp[0] = 1;  // Base case: One way to get weight 0

    // Iterate over bags (powers of 2)
    for (int i = 0; (1 << i) <= n; ++i) { // 1 << i is 2^i
        long long weight = 1 << i; // Current weight of the bag (2^i)

        // For each weight bag
        std::vector<long long> new_dp = dp;  // Copy the current dp for this bag

        // Process the current bag with its weight
        for (int count : magicalNumbers) {
            for (int w = 0; w <= n - weight * count; ++w) {
                if (dp[w] > 0) {
                    new_dp[w + weight * count] = (new_dp[w + weight * count] + dp[w]) % MOD;
                }
            }
        }
        
        dp = new_dp;  // Update dp to the new_dp after processing the current bag
    }

    return dp[n];
}

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<int> magicalNumbers(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> magicalNumbers[i];
    }

    // Get the result
    int result = countWaysToAchieveWeight(n, m, magicalNumbers);
    std::cout << result << std::endl;

    return 0;
}
