#include <iostream>
#include <vector>
#include <climits>

int main() {
    int n;
    std::cin >> n;

    std::vector<int> minimums(n + 1, INT_MAX);
    minimums[1] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            int v = i;
            int to = j;
            int w = (179 * i + 719 * j) % 1000 - 500;
            if (minimums[v] != INT_MAX && minimums[to] > minimums[v] + w) {
            	minimums[to] = minimums[v] + w;
            }
        }
    }

    std::cout << minimums[n] << std::endl;

    return 0;
}