#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n = 0, m = 0;
    std::cin >> n >> m;
    std::vector<int> s1(n);
    for (int i = 0; i < n; i++) {
        std::cin >> s1[i];
    }
    std::vector<int> s2(s1.rbegin(), s1.rend());
    const int p = 1000000007;
    const int x_ = 257;
    std::vector<int> h1(n + 1);
    std::vector<int> h2(n + 1);
    std::vector<int> x(n + 1);
    x[0] = 1;
    s1.insert(s1.begin(), 0);
    s2.insert(s2.begin(), 0);
    for (int i = 1; i <= n; i++) {
        h1[i] = (1LL * h1[i - 1] * x_ + s1[i]) % p;
        h2[i] = (1LL * h2[i - 1] * x_ + s2[i]) % p;
        x[i] = 1LL * x[i - 1] * x_ % p;
    }

    auto mirror = [&](int from1, int from2, int slen) {
        return ((h1[from1 + slen - 1] + 1LL * h2[from2 - 1] * x[slen]) % p ==
                (h2[from2 + slen - 1] + 1LL * h1[from1 - 1] * x[slen]) % p);
    };

    std::vector<int> ans;
    for (int i = 0; i < (n + 2) / 2; i++) {
        if (mirror(1, n - 2 * i + 1, i)) {
            ans.push_back(n - i);
        }
    }
    for (int i = ans.size() - 1; i >= 0; i -= 1) {
        std::cout << ans[i] << ' ';
    }

    return 0;
}