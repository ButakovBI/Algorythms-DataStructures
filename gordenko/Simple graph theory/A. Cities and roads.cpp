#include <iostream>

int main() {
    int n = 0;
    std::cin >> n;
    int cnt = 0;
    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < n; j += 1) {
            int value = 0;
            std::cin >> value;
            cnt += value;
        }
    }
    std::cout << cnt / 2 << '\n';

    return 0;
}