#include <iostream>
#include <vector>
#include <queue>
#include <climits>

int main() {
    int num = 0;
    std::cin >> num;
    for (int start = 0; start < num; start++) {
        int n = 0, m = 0;
        std::cin >> n >> m;
        std::vector< std::vector<std::pair<int, int>> > g(n);
        std::vector<int> lengths(n, 2009000999);
        for (int i = 0; i < m; i++) {
            int u = 0, v = 0, w = 0;
            std::cin >> u >> v >> w;
            g[u].push_back(make_pair(v, w));
            g[v].push_back(make_pair(u, w));
        }

        int s = 0;
        std::cin >> s;
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
        pq.push(std::make_pair(0, s));
        lengths[s] = 0;
        while (!pq.empty()) {
            int v = pq.top().second;
            int cur_length = pq.top().first;
            pq.pop();
            if (cur_length > lengths[v]) {
                continue;
            }
            for (auto& edge : g[v]) {
                int to = edge.first;
                int weight = edge.second;
                int distance = cur_length + weight;
                if (distance < lengths[to]) {
                    lengths[to] = distance;
                    pq.push(make_pair(distance, to));
                }
            }
        }
        for (int i = 0; i < n; i++) {
            std::cout << lengths[i] << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}