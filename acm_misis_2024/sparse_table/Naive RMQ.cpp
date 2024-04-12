#include <iostream>
#include <fstream>
#include <vector>

int main() {
    std::ifstream fin("sparse.in");
    std::ofstream fout("sparse.out");

    int n = 0, m = 0, a1 = 0, u1 = 0, v1 = 0;
    fin >> n >> m >> a1 >> u1 >> v1;

    std::vector<int> a(n);
    int log_n = 0;
    while ((1 << (log_n + 1)) <= n) {
        log_n++;
    }
    a[0] = a1;
    for (int i = 1; i < n; i += 1) {
        a[i] = (23 * a[i - 1] + 21563) % 16714589;
    }
    std::vector<std::vector<int>> sparse_table(n, std::vector<int>(log_n + 1));
    for (int i = 0; i < n; i += 1) {
        sparse_table[i][0] = a[i];
    }
    for (int j = 1; j <= log_n; j += 1) {
        for (int i = 0; i + (1 << j) - 1 < n; i += 1) {
            sparse_table[i][j] = std::min(sparse_table[i][j - 1], sparse_table[i + (1 << (j - 1))][j - 1]);
        }
    }

    int u = u1, v = v1;
    int len = std::max(u, v) - std::min(u, v) + 1;
    int j = 0;
    while ((1 << (j + 1)) <= len) {
        j++;
    }
    int ans = std::min(sparse_table[std::min(u, v) - 1][j], sparse_table[std::max(u, v) - (1 << j)][j]);
    for (int i = 1; i < m; i++) {
        u = ((17 * u + 751 + ans + 2 * i) % n) + 1;
        v = ((13 * v + 593 + ans + 5 * i) % n) + 1;
        len = std::max(u, v) - std::min(u, v) + 1;
        j = 0;
        while ((1 << (j + 1)) <= len) {
            j++;
        }
        ans = std::min(sparse_table[std::min(u, v) - 1][j], sparse_table[std::max(u, v) - (1 << j)][j]);
    }

    fout << u << ' ' << v << ' ' << ans;

    fin.close();
    fout.close();

    return 0;
}
