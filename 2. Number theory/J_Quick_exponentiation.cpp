#include <iostream>

unsigned long long gcd(unsigned long long a, unsigned long long b) {
    return (b == 0) ? a : gcd(b, a % b);
}

long double my_pow(long double a, int32_t n) {
    if (n == 1 || n == 0) {
        return a;
    }
    return ((n % 2) ? (a * my_pow(a, n - 1)) : (my_pow(a * a, n / 2)));
}


int main() {

    long double a = 0;
    int32_t n = 0;
    std::cin >> a >> n;
    if (n == 0) {
        std::cout << 1;
    }
    else {
        std::cout << my_pow(a, n);
    }

}