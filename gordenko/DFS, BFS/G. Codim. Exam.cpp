#include <iostream>
#include <vector>

bool dfs(std::vector<std::vector<long long>>& graph, std::vector<long long>& colors, long long v, long long color);

int main() {
    long long n = 0, m = 0;
    std::cin >> n >> m;

    std::vector<std::vector<long long>> graph(n + 1);
    for (long long i = 0; i < m; i++) {
        long long v1 = 0, v2 = 0;
        std::cin >> v1 >> v2;
        graph[v1].push_back(v2);
        graph[v2].push_back(v1);
    }

    std::vector<long long> colors(n + 1, -1);
    bool ans = false;
    for (long long i = 1; !ans && i <= n; i += 1) {
        if (colors[i] == -1) {
            if (!dfs(graph, colors, i, 1)) {
                ans = true;
            }
        }
    }

    int cnt = 0;
    std::vector<int> ans_days;
    for (int i = 0; i <= n; i += 1) {
        if (colors[i] == 0) {
            cnt++;
            ans_days.push_back(i);
        }
    }

    if (ans) {
        std::cout << "NO";
    } else {
        std::cout << "YES" << '\n';
        std::cout << cnt << '\n';
        for (int& day : ans_days) {
            std::cout << day << ' ';
        }

    }
    return 0;
}

bool dfs(std::vector<std::vector<long long>>& graph, std::vector<long long>& colors, long long v, long long color) {
    colors[v] = color;
    for (long long& to : graph[v]) {
        if (colors[to] == -1) {
            if (!dfs(graph, colors, to, 1 - color)) {
                return false;
            }
        } else if (colors[to] == color) {
            return false;
        }
    }
    return true;
}