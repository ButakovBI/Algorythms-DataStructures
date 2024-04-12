#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

unsigned long long gcd(unsigned long long a, unsigned long long b) {
    return (b == 0) ? a : gcd(b, a % b);
}

int main() {

    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
    std::cin >> x1 >> y1 >> x2 >> y2;

    int diff_x = std::abs(x2 - x1);
    int diff_y = std::abs(y2 - y1);
    std::cout << gcd(diff_x, diff_y) + 1;

}