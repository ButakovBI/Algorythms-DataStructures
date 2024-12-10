#include <iostream>

unsigned long long gcd(unsigned long long a, unsigned long long b) {
    return (b == 0) ? a : gcd(b, a % b);
}

int main() {
    unsigned long long a = 0;
    unsigned long long b = 0;

    std::cin >> a >> b;

    unsigned long long ans = b / gcd(a, b) * a;

    std::cout << ans;
}