#include <iostream>
#include <vector>

const int inf = 1000000000;

int main() {
    int e = 0, f = 0;
    std::cin >> e >> f;
    int m = f - e;

    int n = 0;
    std::cin >> n;

    std::vector<int> weights(n + 1), costs(n + 1);

    for (int i = 1; i <= n; i += 1) {
        int cost = 0, weight = 0;
        std::cin >> cost >> weight;
        costs[i] = cost;
        weights[i] = weight;
    }

    std::vector<int> dp_min(m + 1, inf);
    dp_min[0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = weights[i]; j <= m; j++) {
            if (dp_min[j - weights[i]] != inf) {
                dp_min[j] = std::min(dp_min[j], dp_min[j - weights[i]] + costs[i]);
            }
        }
    }
    int ans_min = dp_min[m];

    std::vector<int> dp_max(m + 1, -inf);
    dp_max[0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = weights[i]; j <= m; j++) {
            if (dp_max[j - weights[i]] != -inf) {
                dp_max[j] = std::max(dp_max[j], dp_max[j - weights[i]] + costs[i]);
            }
        }
    }

    int ans_max = dp_max[m];

    if (ans_max == -inf || ans_min == inf) {
        std::cout << "This is impossible.";
    }
    else {
        std::cout << ans_min << ' ' << ans_max;
    }

    return 0;
}