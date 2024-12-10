#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>


int main() {
    int n = 0;
    std::cin >> n;


    std::vector<std::vector<int>> graph(n + 1);
    std::vector<int> minimums(n + 1, 1e9);
    std::vector<int> used(n + 1, false);

    for (int i = 1; i <= n; i += 1) {
        int a = 0;
        std::cin >> a;
        graph[a].emplace_back(i);
    }

    std::queue<int> q;
    q.push(1);
    int min_weight = 0;
    minimums[1] = 0;
    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (int& to : graph[v]) {
            if (!used[to]) {
                used[to] = true;
                if (minimums[to] > minimums[v] + 1) {
                    minimums[to] = minimums[v] + 1;
                    if (minimums[to] > min_weight) {
                        min_weight = minimums[to];
                    }
                    q.push(to);
                }
            }
        }
    }
    std::cout << min_weight;

    return 0;

}