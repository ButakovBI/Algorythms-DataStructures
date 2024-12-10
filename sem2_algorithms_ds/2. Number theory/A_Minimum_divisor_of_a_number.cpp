#include <iostream>

int main() {
    int32_t n = 0;

    std::cin >> n;
    int32_t ans = n;
    for (size_t i = 2; i * i <= n; i += 1) {
        if (n % i == 0) {
            ans = i;
            break;
        }
    }
    std::cout << ans;
}