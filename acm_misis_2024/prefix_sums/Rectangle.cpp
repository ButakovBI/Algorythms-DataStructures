#include <iostream>
#include <vector>

int main() {
    int n = 0, m = 0;
    std::cin >> n >> m;
    std::vector<std::vector<int>> prefix(n + 1, std::vector<int>(m + 1, 0));
    int value = 0;
    for (int i = 1; i <= n; i += 1) {
        for (int j = 1; j <= m; j += 1) {
            std::cin >> value;
            prefix[i][j] = value + prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1];
        }
    }
    int ans = -100;
    for (int i1 = 1; i1 <= n; i1 += 1) {
        for (int i2 = i1; i2 <= n; i2 += 1) {
            for (int j1 = 1; j1 <= m; j1 += 1) {
                for (int j2 = j1; j2 <= m; j2 += 1) {
                    ans = std::max(ans, prefix[i1 - 1][j1 - 1] + prefix[i2][j2]
                    - prefix[i1 - 1][j2] - prefix[i2][j1 - 1]);
                }
            }
        }
    }
    std::cout << ans;

    return 0;
}