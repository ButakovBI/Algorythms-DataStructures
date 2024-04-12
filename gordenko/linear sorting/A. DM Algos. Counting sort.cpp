#include <iostream>
#include <vector>

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<int> numbers(n);
    int max_element = -10000, min_element = 10000;
    for (int i = 0; i < n; i += 1) {
        std::cin >> numbers[i];
        if (numbers[i] > max_element) {
            max_element = numbers[i];
        }
        if (numbers[i] < min_element) {
            min_element = numbers[i];
        }
    }

    int size = max_element - min_element + 1;
    std::vector<int> counter(size, 0);
    for (int i = 0; i < n; i += 1) {
        counter[numbers[i] - min_element] += 1;
    }

    for (int i = 1; i < size; i += 1) {
        counter[i] += counter[i - 1];
    }

    std::vector<int> ans(n);
    for (int i = n - 1; i >= 0; i -= 1) {
        ans[counter[numbers[i] - min_element]-- - 1] = numbers[i];
    }

    for (int i = 0; i < n; i += 1) {
        std::cout << ans[i] << ' ';
    }
}

//    5
//    -3 4 1 0 -2