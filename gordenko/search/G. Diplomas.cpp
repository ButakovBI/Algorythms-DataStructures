#include <iostream>

int binary_search_by_answer(int w, int h, int n);

int main() {
    int w = 0, h = 0, n = 0;
    std::cin >> w >> h >> n;
    int res = binary_search_by_answer(w, h, n);
    std::cout << res;
    return 0;
}

int binary_search_by_answer(int w, int h, int n) {
    int start = std::max(w, h);
    int end = n * start;
    while (start < end) {
        int mid = (start + end) / 2;
        if ((mid / w) * (mid / h) > n) {
            end = mid;
        } else {
            start = mid + 1;
        }
    }
    return end;
}