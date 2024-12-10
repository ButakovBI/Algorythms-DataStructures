#include <iostream>

int main() {

    int n = 0;
    std::cin >> n;

    bool incr_flag = true;
    int min_value = 1e9;
    std::cin >> min_value;
    int a = -1;
    int prev = min_value;
    for (int i = 1; incr_flag && i < n; i += 1) {
        std::cin >> a;
        if (a < prev) {
            incr_flag = false;
        } else {
            prev = a;
        }
    }

    int ans = -1;
    if (incr_flag && a >= min_value) {
        ans = a - min_value;
    } else if (n == 1) {
        ans = 0;
    }
    std::cout << ans;

    return 0;
}