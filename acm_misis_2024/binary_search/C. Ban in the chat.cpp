#include <iostream>

long long binary_search(long long k, long long x);
bool check(long long msg, long long k, long long x);

int main() {
    int t = 0;
    std::cin >> t;
    long long k = 0, x = 0;
    for (int i = 0; i < t; i += 1) {
        std::cin >> k >> x;
        std::cout << binary_search(k, x) << '\n';
    }
    return 0;
}

bool check(long long msg, long long k, long long x) {
    bool ans = false;
    long long sum = (1 + msg) * msg / 2;
    if (k < msg) {
        sum = k * k - (k * 2 - msg - 1) * (k * 2 - msg) / 2;
    }
    if (sum >= x) {
        ans = true;
    }
    return ans;
}

long long binary_search(long long k, long long x) {
    long long l = 0, r = 2 * k - 1;
    while (l < r) {
        long long mid = (l + r) / 2;
        if (check(mid, k, x)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    return l;
}
