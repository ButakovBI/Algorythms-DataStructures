#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <tuple>


bool dijkstra(std::vector<std::vector<std::vector<int>>>& g, int n, int a, int b, int needed_time,
              std::vector<int>& path, std::vector<int>& idxs) {
    std::vector<int> prices(n, 1e9 + 1);
    std::vector<int> time(n, 0);
    prices[a - 1] = 0;
    std::priority_queue<std::pair<int, int>> pq;
    pq.push({a - 1, 0});

    while (!pq.empty()) {
        int v = pq.top().second;
        int cur_price = pq.top().first;
        pq.pop();

        if (cur_price > prices[v]) {
            continue;
        }

        for (auto& edge : g[v]) {
            int to = edge[0];
            int idx = edge[1];
            int sec = edge[2];
            int price = edge[3];

            if (time[v] + sec <= needed_time && prices[v] + price < prices[to]) {
                time[to] = time[v] + sec;
                prices[to] = prices[v] + price;
                path[to] = v;
                idxs[to] = idx;
                pq.push({prices[to], to});
            }
        }
    }

    return time[b - 1] <= needed_time;
}

int main() {
    int n = 0, m = 0;
    std::cin >> n >> m;

    std::vector<std::vector<std::vector<int>>> g(n);

    for (int i = 0; i < m; i += 1) {
        int u = 0, v = 0, t = 0;
        std::cin >> u >> v >> t;
        g[u - 1].push_back({v - 1, 0, t, 0});
        g[v - 1].push_back({u - 1, 0, t, 0});
    }

    int k = 0;
    std::cin >> k;
    int sum_prices = 0;
    for (int i = 0; i < k; i++) {
        int u = 0, v = 0, minute = 0, price = 0;
        std::cin >> u >> v >> minute >> price;
        g[u - 1].push_back({v - 1, i + 1, minute, price});
        g[v - 1].push_back({u - 1, i + 1, minute, price});
        sum_prices += price;
    }

    int p = 0;
    std::cin >> p;

    std::vector<int> path(n, 0);
    std::vector<int> idxs(n, 0);
    std::set<int> offers;
    for (int i = 0; i < p; i += 1) {
        int a = 0, b = 0, t = 0;
        std::cin >> a >> b >> t;
        if (dijkstra(g, n, a, b, t, path, idxs)) {
            while (path[b - 1] != a - 1) {
                offers.insert(idxs[b - 1]);
                b = path[b - 1];
            }
        }
    }

    std::cout << offers.size() << '\n';
    for (int elem : offers) {
        std::cout << elem << ' ';
    }

    return 0;
}