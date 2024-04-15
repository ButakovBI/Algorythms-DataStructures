#include <iostream>
#include <vector>
#include <tuple>
#include <queue>


void bfs(int x1, int y1, int x2, int y2, int n) {
    std::vector<int> dx = {-1, -2, -2, -1, 1, 2, 2, 1};
    std::vector<int> dy = {-2, -1, 1, 2, 2, 1, -1, -2};

    std::vector<std::vector<std::vector<int>>> used(n + 1);
    std::queue<std::pair<int, int>> q;
    q.push({x1, y1});
    used[x1][y1] = {x1, y1, 0};

    while (!q.empty()) {
        int cur_x = q.front().first;
        int cur_y = q.front().second;
        q.pop();

        if (cur_x == x2 && cur_y == y2) {
            std::vector<std::pair<int, int>> path;
            int ans = 0;
            while (cur_x != x1 || cur_y != y1) {
                ans++;
                path.push_back({cur_x, cur_y});
                int tmp_x = used[cur_x][cur_y][0];
                int tmp_y = used[cur_x][cur_y][1];
                cur_x = tmp_x;
                cur_y = tmp_y;
            }
            path.push_back({cur_x, cur_y});
            std::cout << ans << '\n';
            for (auto it = path.rbegin(); it != path.rend(); ++it) {
                std::cout << it->first << ' ' << it->second << '\n';
            }
            return;
        }

        for (int i = 0; i < 8; i++) {
            int new_x = cur_x + dx[i];
            int new_y = cur_y + dy[i];
            if (new_x >= 0 && new_x <= n && new_y >= 0 && new_y <= n &&
            used[new_x][new_y][0] == 0 && used[new_x][new_y][1] == 0) {
                used[new_x][new_y] = {cur_x, cur_y};
                q.push({new_x, new_y});
            }
        }
    }
}

int main() {
    int n = 0;
    std::cin >> n;

    int x1, y1, x2, y2;
    std::cin >> x1 >> y1 >> x2 >> y2;

    bfs(x1, y1, x2, y2, n);

    return 0;
}