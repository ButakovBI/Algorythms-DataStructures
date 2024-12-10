#include <algorithm>
#include <iostream>
#include <vector>

int binary_search(std::vector<int>& numbers, int l, int r, int value);

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n = 0;
    std::cin >> n;

    std::vector<int> values(n);
    for (int i = 0; i < n; i += 1) {
        std::cin >> values[i];
    }
    std::sort(values.begin(), values.end());
    int m = 0;
    std::cin >> m;
    int query = 0;
    for (int i = 0; i < m; i += 1) {
        std::cin >> query;
        std::cout << binary_search(values, 0, n - 1, query) << ' ';
    }
}

int binary_search(std::vector<int>& numbers, int l, int r, int value) {
    while (l <= r) {
        int mid = (l + r) / 2;
        if (numbers[mid] > value) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return r + 1;
}