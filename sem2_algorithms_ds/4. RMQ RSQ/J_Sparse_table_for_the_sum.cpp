#include<iostream>
#include<vector>

long long my_sum(const std::vector<std::vector<long long>>& vec, const long long& x1, const long long& y1, const long long& z1, const long long& x2, const long long& y2, const long long& z2, const long long& k, const long long& n, const long long& m) {
    const long long len = vec.size();
    if (z1 == 0) {
        long long ans = 0;
        for (long long i = x1 * m + y1; i < x2 * m + y2 + 1; i += m) {
            for (long long j = i; j <= i + (y2 - y1); j += 1) {
                ans += vec[j][z2];
            }
        }
        return ans;
    }
    else {
        long long ans = 0;
        for (long long i = x1 * m + y1; i < x2 * m + y2 + 1; i += m) {
            for (long long j = i; j <= i + (y2 - y1); j += 1) {
                ans += vec[j][z2] - vec[j][z1 - 1];
            }
        }
        return ans;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    long long n = 0, m = 0, k = 0;
    std::cin >> n >> m >> k;
    std::vector<std::vector<long long>> vec(n * m);
    for (long long i = 0; i < n * m; ++i) {
        std::vector<long long> rows(k);
        long long sum = 0;
        for (long long j = 0; j < k; ++j) {
            long long a = 0;
            std::cin >> a;
            sum += a;
            rows[j] = sum;
        }
        vec[i] = rows;
    }

    long long q = 0;
    std::cin >> q;
    for (long long i = 0; i < q; ++i) {
        long long x1 = 0, y1 = 0, z1 = 0, x2 = 0, y2 = 0, z2 = 0;
        std::cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
        x1 -= 1;
        y1 -= 1;
        z1 -= 1;
        x2 -= 1;
        y2 -= 1;
        z2 -= 1;
        std::cout << my_sum(vec, x1, y1, z1, x2, y2, z2, k, n, m) << "\n";
    }
}