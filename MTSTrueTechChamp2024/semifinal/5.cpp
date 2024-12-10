#include <iostream>
#include <vector>
#include <queue>
#include <limits>

const long long INF = std::numeric_limits<long long>::max();

// Структура для хранения рёбер графа
struct Edge {
    long long to;
    long long cost;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    long long n = 0, s = 0, f = 0;
    std::cin >> n >> s >> f;

    std::vector<std::vector<Edge>> graph(n + 1);
    std::vector<long long> dist(n + 1, INF);
    std::vector<long long> dist_from_1(n + 1, INF);

    // Чтение графа
    for (long long i = 0; i < n - 1; ++i) {
        long long a = 0, b = 0, c = 0;
        std::cin >> a >> b >> c;
        graph[a].push_back({b, c});
        graph[b].push_back({a, c});
    }

    std::vector<std::pair<long long, long long>> air(n + 1);
    for (long long i = 2; i <= n; ++i) {
        long long d = 0, m = 0;
        std::cin >> d >> m;
        air[i] = {d, m};
    }

    // Функция для алгоритма Дейкстры
    auto dijkstra = [&](long long start, std::vector<long long>& dist) {
        std::priority_queue<std::pair<long long, long long>, 
                            std::vector<std::pair<long long, long long>>, 
                            std::greater<>> pq;
        dist[start] = 0;
        pq.push({0, start});

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();

            if (d > dist[u]) continue;
            for (const auto& edge : graph[u]) {
                long long v = edge.to;
                long long new_dist = d + edge.cost;

                if (new_dist < dist[v]) {
                    dist[v] = new_dist;
                    pq.push({new_dist, v});
                }
            }
        }
    };

    // Вычисление расстояний от перекрёстка 1 до всех остальных перекрёстков
    dijkstra(1, dist_from_1);

    // Алгоритм Дейкстры для поиска кратчайшего пути от s до f с учётом аэросамокатов
    std::priority_queue<std::pair<long long, long long>, 
                        std::vector<std::pair<long long, long long>>, 
                        std::greater<>> pq;
    dist[s] = 0;
    pq.push({0, s});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;

        // Обработка обычных дорог
        for (const auto& edge : graph[u]) {
            long long v = edge.to;
            long long new_dist = d + edge.cost;

            if (new_dist < dist[v]) {
                dist[v] = new_dist;
                pq.push({new_dist, v});
            }
        }

        // Обработка аэросамокатов
        if (u > 1) {
            auto [cost, max_range] = air[u];
            for (long long v = 1; v <= n; ++v) {
                if (dist_from_1[u] == dist_from_1[v] && 
                    dist_from_1[v] <= dist_from_1[u] + max_range) {
                    long long new_dist = d + cost;
                    if (new_dist < dist[v]) {
                        dist[v] = new_dist;
                        pq.push({new_dist, v});
                    }
                }
            }
        }
    }

    std::cout << dist[f] << '\n';

    return 0;
}
