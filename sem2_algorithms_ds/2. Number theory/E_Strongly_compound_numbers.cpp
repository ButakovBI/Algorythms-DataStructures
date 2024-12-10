#include <iostream>
#include <vector>

unsigned long long gcd(unsigned long long a, unsigned long long b) {
    return (b == 0) ? a : gcd(b, a % b);
}

bool hasThreePrimeDivisors(int n) {
    int cnt = 0;
    const int num = n;
    for (int i = 2; i * i <= n; i += 1) {
        if (n % i == 0) {
            cnt++;
            if (cnt >= 3) {
                return true;
            }
            while (n % i == 0) {
                n /= i;
            }

        }
    }
    if (n != 1) {
        cnt++;
        return (cnt >= 3);
    }
    return false;
}

int main() {
    int n;
    std::cin >> n;
    for (int i = 2; i <= n; i++) {
        if (hasThreePrimeDivisors(i)) {
            std::cout << i << ' ';
        }
    }
    return 0;
}