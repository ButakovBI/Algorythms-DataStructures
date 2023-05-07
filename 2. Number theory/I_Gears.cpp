#include <iostream>

unsigned long long gcd(unsigned long long a, unsigned long long b) {
    return (b == 0) ? a : gcd(b, a % b);
}

int main() {

    unsigned long long n = 0, k = 0;
    std::cin >> n >> k;
    unsigned long long ans = n / gcd(n, k) * k;
    std::cout << ans;
}