#include <iostream>
#include <vector>

int main() {
    long long n = 0, m = 0, s = 0;
    std::cin >> n >> m >> s;

    std::vector<std::vector<long long>> g(m, std::vector<long long>(3));
    for (long long i = 0; i < m; i++) {
        std::cin >> g[i][0] >> g[i][1] >> g[i][2];
    }

    std::vector<long long> minimums(n, 1e18);
    minimums[s - 1] = 0;

    for (long long i = 0; i < n; i++) {
        for (const auto& edge : g) {
            long long v = edge[0] - 1;
            long long to = edge[1] - 1;
            long long w = edge[2];

            if (minimums[v] < 1e18 && minimums[to] > minimums[v] + w) {
                minimums[to] = minimums[v] + w;
            }
        }
    }

    std::vector<bool> negative_cycle(n, false);

    for (long long i = 0; i < n; i++) {
        for (const auto& edge : g) {
            long long v = edge[0] - 1;
            long long to = edge[1] - 1;
            long long w = edge[2];

            if (minimums[v] != 1e18 && minimums[to] > minimums[v] + w) {
                minimums[to] = -1e18 - 1;
                negative_cycle[to] = true;
            }

            if (negative_cycle[v]) {
                negative_cycle[to] = true;
            }
        }
    }

    for (long long i = 0; i < minimums.size(); i++) {
        if (minimums[i] == 1e18) {
            std::cout << '*' << std::endl;
        }
        else if (negative_cycle[i]) {
            std::cout << '-' << std::endl;
        }
        else {
            std::cout << minimums[i] << std::endl;
        }
    }

    return 0;
}