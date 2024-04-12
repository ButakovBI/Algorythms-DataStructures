#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> taxi;
    int value = 0;
    while (std::cin >> value) {
        taxi.push_back(value);
    }

    int size = taxi.size();
    std::sort(taxi.begin(), taxi.begin() + size / 2);
    std::sort(taxi.begin() + size / 2, taxi.end());

    int ans = 0;
    for (int i = 0; i < size / 2; i += 1) {
        ans += taxi[i] * taxi[size - i - 1];
    }
    std::cout << ans;

    return 0;
}