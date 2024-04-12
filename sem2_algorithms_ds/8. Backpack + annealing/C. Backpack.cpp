#include <iostream>
#include <vector>

int main() {

    int s = 0, n = 0;
    std::cin >> s >> n;

    std::vector<int> weights(n + 1);

    for (int i = 1; i <= n; i += 1) {
        std::cin >> weights[i];
    }

    std::vector<std::vector<bool>> dp(n + 1, std::vector<bool>(s + 1));
    for (int i = 1; i <= n; i += 1) {
        int weight = weights[i];
        if (weight <= s) {
            dp[i][weight] = true;
        }
        for (int j = 1; j <= s; j += 1) {
            dp[i][j] = std::max(dp[i - 1][j], dp[i][j]);
            if (dp[i - 1][j]) {
                if (weight + j <= s) {
                    dp[i][weight + j] = true;
                }
            }
        }
    }

    /* for (auto& elem : dp) {
         for (auto sym : elem) {
             std::cout << sym << ' ';
         }
         std::cout << std::endl;
     }*/
    bool flag = false;
    for (int i = s; i >= 0; i -= 1) {
        if (dp[n][i]) {
            std::cout << i;
            flag = true;
            break;
        }
    }
    if (!flag) {
        std::cout << 0;
    }
}