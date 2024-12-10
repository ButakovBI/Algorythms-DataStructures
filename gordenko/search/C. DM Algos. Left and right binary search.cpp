#include <iostream>
#include <vector>

void binary_search_left(const std::vector<int>& numbers, int to_find, int start, int end, int* res1);
void binary_search_right(const std::vector<int>& numbers, int to_find, int start, int end, int* res2);


int main() {
    int n = 0, m = 0;
    std::cin >> n >> m;
    std::vector<int> numbers(n);
    for (int i = 0; i < n; i += 1) {
        std::cin >> numbers[i];
    }
    int to_find = 0;
    for (int i = 0; i < m; i += 1) {
        std::cin >> to_find;
        int idx1 = -1;
        int idx2 = -1;
        binary_search_left(numbers, to_find, 0, n - 1, &idx1);
        binary_search_right(numbers, to_find, 0, n - 1, &idx2);
        if (idx1 == -1) {
            std::cout << 0 << '\n';
        } else {
            std::cout << idx1 + 1 << ' ' << idx2 + 1 << '\n';
        }
    }

    return 0;
}

void binary_search_left(const std::vector<int>& numbers, int to_find, int start, int end, int* res1) {
    while (start <= end) {
        int mid = (start + end) / 2;
        if (numbers[mid] == to_find) {
            *res1 = mid;
            end = mid - 1;
        } else if (numbers[mid] < to_find) {
            start = mid + 1;
        } else {
            end = mid - 1;
        }
    }
}

void binary_search_right(const std::vector<int>& numbers, int to_find, int start, int end, int* res2) {
    while (start <= end) {
        int mid = (start + end) / 2;
        if (numbers[mid] == to_find) {
            *res2 = mid;
            start = mid + 1;
        } else if (numbers[mid] < to_find) {
            start = mid + 1;
        } else {
            end = mid - 1;
        }
    }
}