#include <iostream>
#include <vector>
#include <queue>

void dfs(std::vector<std::vector<int>>& graph, std::vector<bool>& used,
         std::vector<int>& minimums, std::vector<int>& path, std::queue<int>& q);

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<std::vector<int>> graph(n + 1);
    std::vector<bool> used(n + 1, false);
    std::vector<int> minimums(n + 1, 1e9);
    std::vector<int> path(n + 1, 1e9);
    int value = 0;
    for (int i = 1; i <= n; i += 1) {
        for (int j = 1; j <= n; j += 1) {
            std::cin >> value;
            if (value && j > i) {
                graph[i].emplace_back(j);
                graph[j].emplace_back(i);
            }
        }
    }

    int u = 0, v = 0;
    std::cin >> u >> v;
    minimums[u] = 0;
    path[u] = u;
    std::vector<int> ans;
    std::queue<int> q;
    q.push(u);
    dfs(graph, used, minimums, path, q);

    if (minimums[v] == 1e9) {
        std::cout << -1;
    } else if (minimums[v] != 0) {
        std::cout << minimums[v] << '\n';
        while (path[v] != v) {
            ans.push_back(v);
            v = path[v];
        }
        ans.push_back(u);
        for (auto iter = ans.rbegin(); iter != ans.rend(); iter += 1) {
            std::cout << *iter << ' ';
        }
    } else {
        std::cout << 0;
    }


    return 0;
}

void dfs(std::vector<std::vector<int>>& graph, std::vector<bool>& used,
         std::vector<int>& minimums, std::vector<int>& path, std::queue<int>& q) {
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int &to: graph[v]) {
            if (!used[to]) {
                used[to] = true;
                if (minimums[v] < 1e9 && minimums[to] > minimums[v] + 1) {
                    minimums[to] = minimums[v] + 1;
                    path[to] = v;
                }
                q.push(to);
            }
        }
    }
}