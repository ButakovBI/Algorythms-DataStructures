#include <iostream>
#include <vector>

int main() {
    int n = 0, m = 0;
    std::cin >> n >> m;
    std::vector<int> in(n + 1), out(n + 1);
    for (int i = 0; i < m; i += 1) {
        int v1 = 0, v2 = 0;
        std::cin >> v1 >> v2;
        in[v2]++;
        out[v1]++;
    }
    for (int i = 1; i <= n; i += 1) {
        std::cout << in[i] << '\n' << out[i] << '\n';
    }

    return 0;
}