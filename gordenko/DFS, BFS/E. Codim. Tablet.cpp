#include <iostream>
#include <vector>
#include <queue>

int main() {
    int n = 0, m = 0;
    std::cin >> n >> m;
    std::vector<std::vector<int>> table(n, std::vector<int>(m));
    std::vector<std::vector<int>> ans(n, std::vector<int>(m, 1e9));
    std::vector<std::vector<bool>> used(n, std::vector<bool>(m, false));
    std::queue<std::pair<int, int>> q;
    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < m; j += 1) {
            std::cin >> table[i][j];
            if (table[i][j] == 1) {
                ans[i][j] = 0;
                q.push({i, j});
            }
        }
    }

    while (!q.empty()) {
        int x = q.front().first, y = q.front().second;
        q.pop();
        if (x - 1 >= 0 && !used[x - 1][y] && table[x - 1][y] != 1) {
            used[x - 1][y] = true;
            q.push({x - 1, y});
        }
    }




    return 0;
}