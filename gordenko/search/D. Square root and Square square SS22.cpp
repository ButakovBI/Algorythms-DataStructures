#include <iomanip>
#include <iostream>
#include <cmath>

double float_binary_search(double x);

int main() {
    double x = 0;
    std::cin >> x;
    double res = float_binary_search(x);

    std::cout << std::setprecision(15) << res;

    return 0;
}

double float_binary_search(double x) {
    double start = 0, end = x;
    const double eps = 1e-7;
    while (end - start > eps) {
        double mid = (start + end) / 2;
        if (mid * mid + sqrt(mid) < x) {
            start = mid;
        } else {
            end = mid;
        }
    }
    return start;
}