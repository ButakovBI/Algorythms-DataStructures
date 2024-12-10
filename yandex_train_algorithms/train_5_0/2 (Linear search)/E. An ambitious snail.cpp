#include <algorithm>
#include <iostream>
#include <vector>

struct Berry {
    long long up;
    long long down;
    long long idx;
};

bool compare(const Berry &b1, const Berry &b2) {
    return b1.up - b1.down > b2.up - b2.down;
}

int main() {
    int n = 0;
    std::cin >> n;
    long long max_up = 0, idx_max_up = 0;
    std::vector<Berry> berries(n);
    long long height = 0, max_height = 0;
    std::vector<long long> order;
    for (long long i = 0; i < n; i++) {
        std::cin >> berries[i].up >> berries[i].down;
        if (berries[i].up - berries[i].down <= 0 && max_up <= berries[i].up) {
            max_up = berries[i].up;
            idx_max_up = i + 1;
        }
        berries[i].idx = i + 1;
    }
//    std::cout << max_up << ' ' << idx_max_up;

    std::vector<Berry> up;
    for (int i = 0; i < n; i += 1) {
        if (berries[i].up > berries[i].down && berries[i].idx != idx_max_up) {
            up.push_back(berries[i]);
        }
    }
    std::sort(up.begin(), up.end(), compare);
    for (int i = 0; i < up.size(); i += 1) {
//        std::cout << up[i].up << ' ' << up[i].down << ' ' << up[i].idx << '\n';
        order.push_back(up[i].idx);
        max_height = std::max(max_height, height + up[i].up);
        height += up[i].up - up[i].down;
    }
    if (idx_max_up != 0) {
        order.push_back(idx_max_up);
        max_height = std::max(max_height, height + max_up);
    }
    for (int i = 0; i < n; i += 1) {
        if (berries[i].up < berries[i].down && berries[i].idx != idx_max_up) {
            order.push_back(berries[i].idx);
        }
    }

    std::cout << max_height << '\n';
    for (long long i : order) {
        std::cout << i << ' ';
    }

    return 0;
}
