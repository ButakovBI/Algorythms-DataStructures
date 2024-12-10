#include <iostream>
#include <vector>

int main() {
    int n = 0, m = 0, q = 0;
    std::cin >> n >> m >> q;
    int value = 0;
    std::vector<std::vector<long long>> prefix(n + 1, std::vector<long long>(m + 1));
    for (int i = 1; i <= n; i += 1) {
        for (int j = 1; j <= m; j += 1) {
            std::cin >> value;
            prefix[i][j] = value + prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1];
        }
    }
    for (int i = 0; i < q; i += 1) {
        int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
        std::cin >> x1 >> y1 >> x2 >> y2;
        std::cout << prefix[x2][y2] - prefix[x1 - 1][y2] - prefix[x2][y1 - 1] + prefix[x1 - 1][y1 - 1] << '\n';
    }

    return 0;
}