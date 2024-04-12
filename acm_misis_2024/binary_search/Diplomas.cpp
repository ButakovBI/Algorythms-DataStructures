#include <iostream>

unsigned long long binary_search_by_answer(unsigned long long w, unsigned long long h, unsigned long long n);

int main() {
    unsigned long long w = 0, h = 0, n = 0;
    std::cin >> w >> h >> n;
    std::cout << binary_search_by_answer(w, h, n);
    return 0;
}

unsigned long long binary_search_by_answer(unsigned long long w, unsigned long long h, unsigned long long n) {
    unsigned long long l = std::max(w, h);
    unsigned long long r = n * l;
    while (l < r) {
        unsigned long long mid = (l + r) / 2;
        if ((mid / w) * (mid / h) >= n) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    return l;
}