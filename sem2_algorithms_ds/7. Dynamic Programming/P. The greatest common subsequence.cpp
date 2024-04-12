#include <iostream>
#include <vector>
#include <algorithm>

int main() {

    std::string s1, s2;
    std::cin >> s1 >> s2;

    int n = s1.length();
    int m = s2.length();

    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i += 1) {
        for (int j = 1; j <= m; j += 1) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else {
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    int ans = dp[n][m];
    std::cout << ans << std::endl;

    std::vector<int> ans_i, ans_j;
    int i = n, j = m;

    while (ans > 0) {
        if (s1[i - 1] == s2[j - 1]) {
            ans_i.push_back(i);
            ans_j.push_back(j);
            i -= 1;
            j -= 1;
            ans -= 1;
        }
        else if (dp[i - 1][j] > dp[i][j - 1]) {
            i -= 1;
        }
        else {
            j -= 1;
        }
    }

    std::reverse(ans_i.begin(), ans_i.end());
    std::reverse(ans_j.begin(), ans_j.end());

    for (auto& elem : ans_i) {
        std::cout << elem << ' ';
    }
    std::cout << std::endl;

    for (auto& elem : ans_j) {
        std::cout << elem << ' ';
    }
    std::cout << std::endl;

}
