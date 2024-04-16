#include <iostream>
#include <vector>
#include <tuple>
#include <queue>

void bfs(int x1, int y1, int x2, int y2, int n) {
    std::vector<int> dx = {-1, -2, -2, -1, 1, 2, 2, 1};
    std::vector<int> dy = {-2, -1, 1, 2, 2, 1, -1, -2};

    std::vector<std::vector<std::pair<int, int>>> used(n + 1, std::vector<std::pair<int, int>>(n + 1));
    std::queue<std::pair<int, int>> q;
    q.push({x1, y1});
    used[x1][y1] = {x1, y1};

    while (!q.empty()) {
        int cur_x = q.front().first;
        int cur_y = q.front().second;
        q.pop();

        if (cur_x == x2 && cur_y == y2) {
            int ans = 0;
            while (cur_x != x1 || cur_y != y1) {
                ans++;
                int tmp_x = used[cur_x][cur_y].first;
                int tmp_y = used[cur_x][cur_y].second;
                cur_x = tmp_x;
                cur_y = tmp_y;
            }
            if (ans % 2 == 0) {
                std::cout << ans / 2;
            } else if (ans > 8) {
                std::cout << (ans + 1) / 2;
            } else {
                std::cout << -1;
            }
            return;
        }

        for (int i = 0; i < 8; i++) {
            int new_x = cur_x + dx[i];
            int new_y = cur_y + dy[i];
            if (new_x >= 0 && new_x <= n && new_y >= 0 && new_y <= n && used[new_x][new_y] == std::make_pair(0, 0)) {
                used[new_x][new_y] = {cur_x, cur_y};
                q.push({new_x, new_y});
            }
        }
    }
}

int main() {

    char sym1 = 0, sym2 = 0;
    int y1 = 0, y2 = 0;
    std::cin >> sym1 >> y1 >> sym2 >> y2;
    int x1 = sym1 - 'a' + 1, x2 = sym2 - 'a' + 1;

    bfs(x1, y1, x2, y2, 8);

    return 0;
}