#include <iostream>
#include <map>

int main() {
    int n = 0;
    std::cin >> n;
    std::map<int, int> counter;
    int value = 0;
    for (int i = 0; i < n; i += 1) {
        std::cin >> value;
        counter[value]++;
    }
    std::pair<int, int> prev;
    bool flag = false;
    int max_pair = 0;
    int max_count = 0;
    for (auto& elem : counter) {
        if (prev.first + 1 == elem.first) {
            flag = true;
            max_pair = std::max(max_pair, elem.second + prev.second);
        }
        max_count = std::max(max_count, elem.second);
        prev = elem;
    }
    if (flag) {
        std::cout << n - max_pair;
    } else {
        std::cout << n - max_count;
    }

    return 0;
}