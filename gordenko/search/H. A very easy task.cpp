#include <iostream>

int binary_search_by_answer(int n, int x, int y);
int check(int time, int x, int y);

int main() {
    int n = 0;
    int x = 0, y = 0;
    std::cin >> n >> x >> y;
    n -= 1;
    int res = binary_search_by_answer(n, x, y) + std::min(x, y);
    std::cout << res;
}

int check(int time, int x, int y) {
    return time / x + time / y;
}

int binary_search_by_answer(int n, int x, int y) {
    int start = 0;
    int end = std::max(x, y) * n;

    while (start < end) {
//        std::cout << start << ' ' << end << std::endl;
        int mid = (start + end) / 2;
        int count = check(mid, x, y);
        if (count >= n) {
            end = mid;
        } else {
            start = mid + 1;
        }
    }
    return end;
}