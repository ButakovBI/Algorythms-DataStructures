#include <iostream>

int32_t gcd(int32_t a, int32_t b) {
    return (b == 0) ? a : gcd(b, a % b);
}

int main() {
    int32_t a = 0;
    int32_t b = 0;

    std::cin >> a >> b;

    std::cout << gcd(a, b);
}