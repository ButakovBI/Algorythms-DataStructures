#include <iostream>
#include <vector>

int binary_search(const std::vector<int>& numbers, int to_find, int start, int end);

int main() {

    int n = 0;
    std::cin >> n;
    std::vector<int> numbers(n);
    for (int i = 0; i < n; i += 1) {
        std::cin >> numbers[i];
    }

    int k = 0;
    std::cin >> k;
    int to_find = 0;
    for (int i = 0; i < k; i += 1) {
        std::cin >> to_find;
        int res = binary_search(numbers, to_find, 0, n - 1);
        if (res != -1) {
            res += 1;
        }
        if (i == 0) {
            std::cout << res;
        } else {
            std::cout << ' ' << res;
        }
    }

    return 0;
}

int binary_search(const std::vector<int>& numbers, int to_find, int start, int end) {
    int ans_idx = -1;
    while (start <= end) {
        int mid = (start + end) / 2;
        if (numbers[mid] == to_find) {
            ans_idx = mid;
            start = end + 1;
        } else if (numbers[mid] < to_find) {
            start = mid + 1;
        } else {
            end = mid - 1;
        }
    }
    return ans_idx;
}