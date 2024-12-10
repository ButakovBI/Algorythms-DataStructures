#include <iostream>

int main() {
    int n = 0;
    std::cin >> n;
    int value = 0;
    int sum = 0, max_value = 0;
    for (int i = 0; i < n; i += 1) {
        std::cin >> value;
        if (value > max_value) {
            max_value = value;
        }
        sum += value;
    }

    if (sum - max_value < max_value) {
        std::cout << 2 * max_value - sum;
    } else {
        std::cout << sum;
    }

    return 0;
}