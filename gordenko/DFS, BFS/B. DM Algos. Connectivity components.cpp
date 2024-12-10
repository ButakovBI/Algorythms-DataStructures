#include <iostream>
#include <vector>

void dfs(std::vector<bool>& used, std::vector<std::vector<int>>& graph, int vertex, int& sum, std::vector<int>& verts);

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
    int components = 0;
    std::vector<int> sums;
    std::vector<std::vector<int>> component_vertexes;
    for (int i = 1; i <= n; i += 1) {
        if (!used[i]) {
            components++;
            int sum = 0;
            std::vector<int> vertexes;
            dfs(used, graph, i, sum, vertexes);
            sums.push_back(sum);
            component_vertexes.push_back(vertexes);
        }
    }

    std::cout << components << '\n';
    for (int i = 0; i < components; i += 1) {
        std::cout << sums[i] << '\n';
        for (int& v : component_vertexes[i]) {
            std::cout << v << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}

void dfs(std::vector<bool>& used, std::vector<std::vector<int>>& graph, int vertex, int& sum, std::vector<int>& verts) {
    if (used[vertex]) {
        return;
    }
    used[vertex] = true;
    sum++;
    verts.push_back(vertex);
    for (auto& v : graph[vertex]) {
        dfs(used, graph, v, sum, verts);
    }
}
