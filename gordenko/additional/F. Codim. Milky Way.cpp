#include <iostream>
#include <vector>

int main() {
    int n = 0;
    std::cin >> n;
    int value = 0, cnt = value;
    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < n; j += 1) {
            std::cin >> value;
            cnt += value;
        }
    }
    std::cout << cnt / 2;

    return 0;
}