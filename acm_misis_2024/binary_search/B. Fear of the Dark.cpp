#include <cmath>
#include <iomanip>
#include <iostream>

double binary_search(long long px, long long py, long long ax, int ay, int bx, int by);
bool check(int px, int py, int ax, int ay, int bx, int by, double w);

int main() {
    int t = 0;
    std::cin >> t;
    int px = 0, py = 0;
    int ax = 0, ay = 0;
    int bx = 0, by = 0;
    for (int i = 0; i < t; i += 1) {
        std::cin >> px >> py;
        std::cin >> ax >> ay;
        std::cin >> bx >> by;
        std::cout << std::setprecision(7) << binary_search(px, py, ax, ay, bx, by) << '\n';
    }
    return 0;
}

double dist(int x1, int y1, int x2, int y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

bool check(int px, int py, int ax, int ay, int bx, int by, double w) {
    double dist_a = dist(ax, ay, px, py);
    double dist_b = dist(bx, by, px, py);
    double dist1 = std::min(std::max(dist_a, dist(ax, ay, 0, 0)),
                            std::max(dist_b, dist(bx, by, 0, 0)));
    double dist2 = std::max(std::max(dist(ax, ay, bx, by) / 2,
                                     dist(ax, ay, 0, 0)),
                                     dist(bx, by, px, py));
    double dist3 = std::max(std::max(dist(ax, ay, bx, by) / 2,
                                     dist(bx, by, 0, 0)),
                                     dist(ax, ay, px, py));
    bool ans = false;
    if (std::min(std::min(dist1, dist2), dist3) <= w) {
        ans = true;
    }
    return ans;
}


double binary_search(int px, int py, int ax, int ay, int bx, int by) {
    double l = 0, r = std::max(sqrt(ax * ax + ay * ay), sqrt(bx * bx + by * by)) + sqrt(px * px + py * py);
    double eps = 1e-7;
    while (l <= r) {
        double mid = (l + r) / 2;
        if (check(px, py, ax, ay, bx, by, mid)) {
            r = mid - eps;
        } else {
            l = mid + eps;
        }
    }
    return r;
}