#include <iostream>
#include <vector>
#include <queue>


void bfs(std::vector<std::vector<int>>& used, std::queue<std::pair<int, int>>& queue,
         const int& n, const int& m) {
    while (!queue.empty()) {
        std::pair<int, int> point = queue.front();
        int x = point.first;
        int y = point.second;
        queue.pop();

        if (x > 0) {
            if (y > 0) {
                if (used[x - 1][y - 1] == 2500) {
                    used[x - 1][y - 1] = used[x][y] + 1;
                    queue.emplace(x - 1, y - 1);
                }
            }

            if (y < m - 1) {
                if (used[x - 1][y + 1] == 2500) {
                    used[x - 1][y + 1] = used[x][y] + 1;
                    queue.emplace(x - 1, y + 1);
                }
            }
        }

        if (x < n - 1) {
            if (y > 0) {
                if (used[x + 1][y - 1] == 2500) {
                    used[x + 1][y - 1] = used[x][y] + 1;
                    queue.emplace(x + 1, y - 1);
                }
            }

            if (y < m - 1) {
                if (used[x + 1][y + 1] == 2500) {
                    used[x + 1][y + 1] = used[x][y] + 1;
                    queue.emplace(x + 1, y + 1);
                }
            }
        }

        for (int index = 0; index < n; index++) {
            for (int jindex = 0; jindex < m; jindex++) {
                std::cout << used[index][jindex] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}


int main() {

    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> used(n, std::vector<int>(m, 2500));
    std::queue<std::pair<int, int>> queue;

    for (int index = 0; index < n; index++) {
        for (int jindex = 0; jindex < m; jindex++) {
            int value;
            std::cin >> value;
            if (value == 1) {
                used[index][jindex] = 0;
                queue.emplace(index, jindex);
            }
        }
    }

    bfs(used, queue, n, m);

    for (int index = 0; index < n; index++) {
        for (int jindex = 0; jindex < m; jindex++) {
            std::cout << used[index][jindex] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
