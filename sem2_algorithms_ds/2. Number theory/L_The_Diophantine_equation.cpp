#include <iostream>
#include <tuple>

long long gcd(long long a, long long b) {
    return (b == 0) ? a : gcd(b, a % b);
}

long long gcdBigFkliD(long long a, long long b, long long& x, long long& y) {
    if (a == 0) {
        x = 0; y = 1;
        return b;
    }
    long long x1 = 0, y1 = 0;
    long long d = gcdBigFkliD(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

std::tuple<long long, long long, long long> gcdExt(long long a, long long b)
{
    if (a == 0) {
        return std::make_tuple(b, 0, 1);
    }
    long long gcd = 0, x = 0, y = 0;
    std::tie(gcd, x, y) = gcdExt(b % a, a);

    return std::make_tuple(gcd, (y - (b / a) * x), x);
}

int main() {

    int t = 0;
    std::cin >> t;
    for (int i = 0; i < t; ++i) {
        long long a = 0, b = 0, c = 0;
        std::cin >> a >> b >> c;
        if (c % b == 0) {
            std::cout << 0 << ' ' << c / b << std::endl;
            continue;
        }
        long long num1 = std::max(gcd(a, c), gcd(b, c)), num2 = std::min(gcd(a, c), gcd(b, c));
        if (num1 % num2 == 0 && num1 != 1 && num2 != 1) {
            a /= num2;
            b /= num2;
            c /= num2;
        }
        long long d = 0, x = 0, y = 0;
        std::tuple<long long, long long, long long> tup = gcdExt(a, b);
        d = std::get<0>(tup);
        x = std::get<1>(tup);
        y = std::get<2>(tup);
        if (!(c % d)) {
            x *= c / d;
            y *= c / d;
            long long k = (std::abs(x) + (b / d) - 1) / (b / d);
            if (x > 0) {
                x -= b / d * (k - 1);
                y += a / d * (k - 1);
            }
            else {
                x += b / d * k;
                y -= a / d * k;
            }
            std::cout << x << ' ' << y << std::endl;
        }
        else {
            std::cout << 0 << ' ' << 0 << std::endl;
        }
    }
    return 0;
}