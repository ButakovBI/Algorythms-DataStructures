#include <iostream>
#include <vector>

int main() {
    int n = 0, s = 0, f = 0;
    std::cin >> n >> s >> f;

    std::vector<std::vector<int>> d(n, std::vector<int>(n));
    std::vector<std::vector<int>> g(n);
    std::vector<int> path(n, 0);
    std::vector<int> lengths(n, 1e9);

    for (int i = 0; i < n; i += 1) {
        std::vector<int> numbers(n);
        for (int j = 0; j < n; j += 1) {
            std::cin >> numbers[j];
            d[i][j] = numbers[j];
            if (j != i && numbers[j] != -1) {
                g[i].push_back(j);
            }
        }
    }

    lengths[s - 1] = 0;
    std::vector<bool> used(n, false);
    int min_elem = 1e9 + 1;
    while (min_elem != 1e9) {
        min_elem = 1e9;
        int min_idx = n - 1;
        for (int i = 0; i < n; i += 1) {
            if (!used[i] && lengths[i] < min_elem) {
                min_elem = lengths[i];
                min_idx = i;
            }
        }
        used[min_idx] = true;
        for (int to : g[min_idx]) {
            if (lengths[to] > lengths[min_idx] + d[min_idx][to]) {
                lengths[to] = lengths[min_idx] + d[min_idx][to];
                path[to] = min_idx;
            }
        }
    }

    if (lengths[f - 1] == 1e9) {
        std::cout << -1 << '\n';
    } else {
        std::vector<int> ans;
        ans.push_back(f);
        while (ans.back() != s) {
            ans.push_back(path[ans.back() - 1] + 1);
        }
        for (int i = ans.size() - 1; i >= 0; --i) {
            std::cout << ans[i] << " ";
        }
        std::cout << '\n';
    }

    return 0;
}