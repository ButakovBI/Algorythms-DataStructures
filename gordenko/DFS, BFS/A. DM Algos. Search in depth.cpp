#include <iostream>
#include <vector>

void dfs(std::vector<bool>& used, std::vector<std::vector<int>>& graph, int vertex, int& sum);

int main() {
    int n = 0, m = 0;
    std::cin >> n >> m;

    std::vector<bool> used(n + 1, false);
    std::vector<std::vector<int>> graph(n + 1);

    for (int i = 0; i < m; i += 1) {
        int v1 = 0, v2 = 0;
        std::cin >> v1 >> v2;
        graph[v1].push_back(v2);
        graph[v2].push_back(v1);
    }
    int sum = 0;
    dfs(used, graph, 1, sum);

    std::cout << sum << '\n';
    for (int i = 1; i <= n; i += 1) {
        if (used[i]) {
            std::cout << i << ' ';
        }
    }

    return 0;
}

void dfs(std::vector<bool>& used, std::vector<std::vector<int>>& graph, int vertex, int& sum) {
    if (used[vertex]) {
        return;
    }
    used[vertex] = true;
    sum++;
    for (auto& v : graph[vertex]) {
        dfs(used, graph, v, sum);
    }
}
