#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

int bfs(int x1, int y1, int x2, int y2, int n);

int main() {

    char sym1 = 0, sym2 = 0;
    int y1 = 0, y2 = 0;
    std::cin >> sym1 >> y1 >> sym2 >> y2;
    int x1 = sym1 - 'a' + 1, x2 = sym2 - 'a' + 1;

    const int n = 8;
    std::cout << bfs(x1, y1, x2, y2, n);


    return 0;
}

int bfs(int x1, int y1, int x2, int y2, int n) {
    std::vector<int> dx = {-1, -2, -2, -1, 1, 2, 2, 1};
    std::vector<int> dy = {-2, -1, 1, 2, 2, 1, -1, -2};

    std::vector<std::vector<bool>> used1(n + 1, std::vector<bool>(n + 1, false));
    std::vector<std::vector<bool>> used2(n + 1, std::vector<bool>(n + 1, false));
    std::vector<std::vector<int>> minimums1(n + 1, std::vector<int>(n + 1, 1e9));
    std::vector<std::vector<int>> minimums2(n + 1, std::vector<int>(n + 1, 1e9));
    minimums1[x1][y1] = 0;
    minimums2[x2][y2] = 0;
    std::queue<std::pair<int, int>> q1, q2;
    q1.emplace(x1, y1);
    q2.emplace(x2, y2);
    used1[x1][y1] = true;
    used2[x2][y2] = true;

    while (!q1.empty() && !q2.empty()) {
        int cur_x1 = q1.front().first;
        int cur_x2 = q2.front().first;
        int cur_y1 = q1.front().second;
        int cur_y2 = q2.front().second;
        q1.pop();
        q2.pop();
        used1[cur_x1][cur_y1] = true;
        used2[cur_x2][cur_y2] = true;

        for (int i = 0; i < 8; i++) {
            int new_x1 = cur_x1 + dx[i];
            int new_x2 = cur_x2 + dx[i];
            int new_y1 = cur_y1 + dy[i];
            int new_y2 = cur_y2 + dy[i];
            if (new_x1 >= 1 && new_x1 <= n && new_y1 >= 1 && new_y1 <= n && !used1[new_x1][new_y1]) {
                if (minimums1[new_x1][new_y1] > minimums1[cur_x1][cur_y1] + 1) {
                    minimums1[new_x1][new_y1] = minimums1[cur_x1][cur_y1] + 1;
                    q1.emplace(new_x1, new_y1);
                }
            }
            if (new_x2 >= 1 && new_x2 <= n && new_y2 >= 1 && new_y2 <= n && !used2[new_x2][new_y2]) {
                if (minimums2[new_x2][new_y2] > minimums2[cur_x2][cur_y2] + 1) {
                    minimums2[new_x2][new_y2] = minimums2[cur_x2][cur_y2] + 1;
                    q2.emplace(new_x2, new_y2);
                }
            }
        }
    }
//    for (auto& elem : minimums1) {
//        for (auto& el : elem) {
//            std::cout << el << ' ';
//        }
//        std::cout << '\n';
//    }
    int ans = 1e9;
    for (int i = 1; i <= n; i += 1) {
        for (int j = 1; j <= n; j += 1) {
            if (minimums1[i][j] == minimums2[i][j] && minimums1[i][j] < ans) {
                ans = minimums1[i][j];
            }
        }
    }
    if (ans == 1e9) {
        ans = -1;
    }

    return ans;
}