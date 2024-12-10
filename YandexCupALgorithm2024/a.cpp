#include <iostream>
#include <numeric>


long long lcm(long long a, long long b) {
    return a / std::gcd(a, b) * b;
}


int main() {
    long long a = 0, b = 0, c = 0;
    std::cin >> a >> b >> c;
    long long n = 0;
    std::cin >> n;

    long long ab = lcm(a, b);
    long long ac = lcm(a, c);
    long long bc = lcm(b, c);

    long long abc = lcm(ab, c);

    long long left = 1, right = 1e18, result = -1;
    while (left <= right) {
        long long mid = (left + right) / 2;

        long long cnt = (mid / ab) + (mid / ac) + (mid / bc) - 3 * (mid / abc);

        if (cnt >= n) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    std::cout << result;

    return 0;
}