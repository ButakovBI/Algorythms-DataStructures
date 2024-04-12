#include <iostream>
#include <vector>

int main() {
    int n = 0;
    std::cin >> n;
    int min_price = 100;
    int cur_price = 0, cur_weight = 0;
    long long ans = 0;
    for (int i = 0; i < n; i += 1) {
        std::cin >> cur_weight >> cur_price;
        min_price = std::min(min_price, cur_price);
        ans += cur_weight * min_price;
    }
    std::cout << ans;
    return 0;
}