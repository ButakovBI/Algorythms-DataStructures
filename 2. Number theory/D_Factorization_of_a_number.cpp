#include <iostream>
#include <vector>

unsigned long long gcd(unsigned long long a, unsigned long long b) {
    return (b == 0) ? a : gcd(b, a % b);
}

int main() {

    int32_t n = 0;
    std::cin >> n;

    const int num = n;

    std::vector<int32_t> ans;

    for (size_t i = 2; i * i <= n; i += 1) {
        while (n % i == 0) {
            ans.push_back(i);
            n /= i;
        }
    }
    if (n != 1) {
        ans.push_back(n);
    }


    if (ans.empty()) {
        std::cout << n;
    }
    else {
        for (size_t idx = 0; idx < ans.size() - 1; idx += 1) {
            std::cout << ans[idx] << ' ';
        }
        std::cout << ans[ans.size() - 1];
    }
}