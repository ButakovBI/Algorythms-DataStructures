#include <iostream>

int main() {
    int k = 0;
    std::cin >> k;

    int x_max = -1e9, y_max = -1e9, x_min = 1e9, y_min = 1e9;
    int x = 0, y = 0;
    for (int i = 0; i < k; i += 1) {
        std::cin >> x >> y;
        if (x > x_max) {
            x_max = x;
        }
        if (x < x_min) {
            x_min = x;
        }
        if (y > y_max) {
            y_max = y;
        }
        if (y < y_min) {
            y_min = y;
        }
    }
    std::cout << x_min << ' ' << y_min << ' ' << x_max << ' ' << y_max;

    return 0;
}