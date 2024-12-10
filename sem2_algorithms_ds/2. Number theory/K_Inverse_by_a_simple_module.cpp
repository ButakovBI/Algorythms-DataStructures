#include <iostream>
#include <tuple>

unsigned long long gcd(unsigned long long a, unsigned long long b) {
    return (b == 0) ? a : gcd(b, a % b);
}

unsigned long long my_pow(unsigned long long a, int32_t n) {
    if (n == 1 || n == 0) {
        return a;
    }
    return ((n % 2) ? ((a * my_pow(a, n - 1)) % 1000000009) : ((my_pow(a * a, n / 2)) % 1000000009));
}

std::tuple<unsigned long long, unsigned long long, unsigned long long> evklid(unsigned long long a, unsigned long long b) {
    if (a == 0) {
        return std::make_tuple(b, 0, 1);
    }
    unsigned long long gcd = 0, x = 0, y = 0;

    std::tie(gcd, x, y) = evklid(b % a, a);

    return std::make_tuple(gcd, (y - (b / a) * x), x);
}

unsigned long long gcdNew(unsigned long long a, unsigned long long b, unsigned long long& x, unsigned long long& y) {
    if (a == 0) {
        x = 0; y = 1;
        return b;
    }
    unsigned long long x1 = 0, y1 = 0;
    unsigned long long d = gcdNew(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

unsigned long long binpow(unsigned long long a, unsigned long long b, unsigned long long m) {
    a %= m;
    unsigned long long ans = 1;
    while (b > 0) {
        if (b % 2) {
            ans = (ans * a) % m;
        }
        a = (a * a) % m;
        b /= 2;
    }
    return ans;
}


int main() {

    const unsigned long long m = 1000000009;
    int t = 0;
    std::cin >> t;
    for (int i = 0; i < t; ++i) {
        unsigned long long a = 0;
        std::cin >> a;

        std::cout << binpow(a, m - 2, m) << std::endl;
    }
}