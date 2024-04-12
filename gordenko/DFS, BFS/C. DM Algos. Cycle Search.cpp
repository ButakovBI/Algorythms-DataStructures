#include <algorithm>
#include <iostream>
#include <vector>

void dfs(std::vector<int>& used, std::vector<std::vector<int>>& graph, std::vector<int>& path,
         int vertex, int parent, bool& ans);

int main() {
    int n = 0;
    std::cin >> n;

    std::vector<int> used(n + 1, 0);
    std::vector<std::vector<int>> graph(n + 1);

    for (int i = 1; i <= n; i += 1) {
        for (int j = 1; j <= n; j += 1) {
            int v = 0;
            std::cin >> v;
            if (v) {
                graph[i].push_back(j);
            }
        }
    }

    bool ans = false;
    std::vector<int> path;
    for (int i = 1; !ans && i <= n; i += 1) {
        if (!used[i]) {
            dfs(used, graph, path, i, -1,  ans);
        }
    }

    if (!ans) {
        std::cout << "NO";
    }

    return 0;
}

void dfs(std::vector<int>& used, std::vector<std::vector<int>>& graph, std::vector<int>& path,
         int vertex, int parent, bool& ans) {
    used[vertex] = 1;
    path.push_back(vertex);

    for (auto& v : graph[vertex]) {
        if (used[v] == 0) {
            dfs(used, graph, path, v, vertex,  ans);
        } else if (used[v] == 1 && v != parent && !ans) {
            ans = true;
            std::cout << "YES" << '\n';
            int start_idx = std::find(path.begin(), path.end(), v) - path.begin();
            std::cout << path.size() - start_idx << '\n';
            for (int i = start_idx; i < path.size(); i += 1) {
                std::cout << path[i] << ' ';
            }
        }
    }
    used[vertex] = 2;
    path.pop_back();
}
