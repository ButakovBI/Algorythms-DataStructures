#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int q = 0;
    std::cin >> q;
    std::vector<std::vector<int>> players(q, std::vector<int>(5));
    for (int i = 0; i < q; i += 1) {
        std::cin >> players[i][0] >> players[i][1] >> players[i][2] >> players[i][3] >> players[i][4];
    }
    int m = 0, n = 0;
    std::cin >> m >> n;
    std::vector<std::vector<int>> matrix(m, std::vector<int>(n));
    std::vector<std::vector<int>> prefix(m + 1, std::vector<int>(n + 1, 0));
    for (int i = 0; i < q; i += 1) {
        int x1 = players[i][0];
        int y1 = players[i][1];
        int x2 = players[i][2];
        int y2 = players[i][3];
        int a = players[i][4];

        prefix[x1 - 1][y1 - 1] += a;
        prefix[x2][y2] += a;
        prefix[x1 - 1][y2] -= a;
        prefix[x2][y1 - 1] -= a;
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 1; j < n; ++j) {
            prefix[i][j] += prefix[i][j - 1];
        }
    }

    for (int j = 0; j < n; ++j) {
        for (int i = 1; i < m; ++i) {
            prefix[i][j] += prefix[i - 1][j];
        }
    }

    for (int i = 0; i < m; i += 1) {
        for (int j = 0; j < n; j += 1) {
            std::cin >> matrix[i][j];
            std::cout << matrix[i][j] + prefix[i][j] << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}

//2
//1 1 3 3 4
//1 2 2 3 5
//6 6
//0 0 0 0 0 0
//0 0 0 0 0 0
//0 0 0 0 0 0
//0 0 0 0 0 0
//0 0 0 0 0 0
//0 0 0 0 0 0
