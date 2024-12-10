#include <iostream>
#include <vector>

int main() {
    int n = 0, m = 0;
    std::cin >> n >> m;
    std::vector<std::vector<int>> prefix(n + 1, std::vector<int>(m + 1, 0));
    int value = 0;
    for (int i = 1; i < n + 1; i += 1) {
        for (int j = 1; j < m + 1; j += 1) {
            std::cin >> value;
            prefix[i][j] = value + prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1];
            std::cout << prefix[i][j] << ' ';
        }
        std::cout << '\n';
    }
    int ans = prefix[1][1];
    for (int i = 1; i < n + 1; i += 1) {
        for (int j = 1; j < m + 1; j += 1) {
            ans = std::max(prefix[i][j], ans);
            ans = std::max(ans, prefix[i][j] - prefix[i][j - 1]);
            ans = std::max(ans, prefix[i][j] - prefix[i - 1][j]);
            
        }
    }
    std::cout << ans;
    return 0;
}