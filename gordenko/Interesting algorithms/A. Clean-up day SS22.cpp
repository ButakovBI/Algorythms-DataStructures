#include <algorithm>
#include <iostream>
#include <vector>

int binary_search_by_answer(const std::vector<int>& vec, int n, int r, int c);

int main() {
    int n = 0, r = 0, c = 0;
    std::cin >> n >> r >> c;
    std::vector<int> lengths(n);
    for (int i = 0; i < n; i += 1) {
        std::cin >> lengths[i];
    }
    std::sort(lengths.begin(), lengths.end());
    int res = binary_search_by_answer(lengths, n, r, c);
    std::cout << res;
    return 0;
}

int binary_search_by_answer(const std::vector<int>& vec, int n, int r, int c) {
    int start = 0;
    int end = vec[n - 1] - vec[0];
    while (start <= end) {
        int mid = (start + end) / 2;
        int idx = 0;
        int count = 0;
        while (idx + c - 1 < n) {
            if (vec[idx + c - 1] - vec[idx] <= mid) {
                count += 1;
                idx += c;
            } else {
                idx += 1;
            }
        }
        if (count >= r) {
            end = mid - 1;
        } else {
            start = mid + 1;
        }
    }
    return end + 1;
}
