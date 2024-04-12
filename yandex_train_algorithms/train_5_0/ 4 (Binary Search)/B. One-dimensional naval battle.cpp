#include <iostream>

unsigned long long binary_search_by_answer(unsigned long long n);
bool check(unsigned long long mid, unsigned long long n);

int main() {
    unsigned long long n = 0;
    std::cin >> n;
    std::cout << binary_search_by_answer(n);
    return 0;
}

bool check(unsigned long long mid, unsigned long long n) {
    unsigned long long sum = (mid + 1) * mid * (mid + 1) / 2 - mid * (mid + 1) * (2 * mid + 1) / 6;
    return sum + (mid * (mid + 1) / 2) - 1 <= n;
}


unsigned long long binary_search_by_answer(unsigned long long n) {
    unsigned long long l = 0, r = n;
    while (l < r) {
        unsigned long long mid = (l + r + 1) / 2;
        if (check(mid, n)) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }
    return l;
}