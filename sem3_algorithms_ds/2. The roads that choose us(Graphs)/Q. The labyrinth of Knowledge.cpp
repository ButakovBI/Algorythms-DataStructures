#include <iostream>
#include <vector>
#include <limits>

int main() {
    int n = 0, m = 0;
    std::cin >> n >> m;
    std::vector<std::pair<int, std::pair<int, int>>> g(m);
    for (int i = 0; i < m; i++) {
        int u = 0, v = 0, w = 0;
        std::cin >> u >> v >> w;
        u--;
        v--;
        g[i] = {u, {v, w}};
    }
    std::vector<int> maximums(n, std::numeric_limits<int>::min());
    maximums[0] = 0;
    bool changed = true;
    for (int i = 0; i < n && changed; i++) {
        changed = false;
        for (auto edge : g) {
            int v = edge.first;
            int to = edge.second.first;
            int w = edge.second.second;
            if (maximums[v] > std::numeric_limits<int>::min() && maximums[to] < maximums[v] + w) {
                maximums[to] = maximums[v] + w;
                changed = true;
            }
        }
    }
    std::vector<bool> positive_cycle(n, false);
    for (int i = 0; i < n; i++) {
        for (auto edge : g) {
            int v = edge.first;
            int to = edge.second.first;
            int w = edge.second.second;
            if (maximums[v] != std::numeric_limits<int>::min() && maximums[to] < maximums[v] + w) {
                maximums[to] = std::numeric_limits<int>::max();
                positive_cycle[to] = true;
            } else if (positive_cycle[v]) {
                positive_cycle[to] = true;
            }
        }
    }
    if (maximums[n - 1] == std::numeric_limits<int>::min()) {
        std::cout << ":(" << std::endl;
    } else if (positive_cycle[n - 1]) {
        std::cout << ":)" << std::endl;
    } else {
        std::cout << maximums[n - 1] << std::endl;
    }
    return 0;
}