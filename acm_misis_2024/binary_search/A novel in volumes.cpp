#include <algorithm>
#include <iostream>
#include <vector>

bool check(std::vector<int>& pages, int k, int mid);
int binary_search_by_answer(std::vector<int>& pages, int n, int k);

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<int> pages(n);
    for (int i = 0; i < n; i++) {
        std::cin >> pages[i];
    }
    int k = 0;
    std::cin >> k;
    std::cout << binary_search_by_answer(pages, n, k);

    return 0;
}

bool check(std::vector<int>& pages, int k, int mid) {
    int s = mid;
    int j = 0;
    for (int i = 0; i < k; i++) {
        j = std::upper_bound(pages.begin(), pages.end(), s) - pages.begin();
        s = pages[j - 1] + mid;
    }
    if (s - mid >= pages.back()) {
        return false;
    }
    return true;
}

int binary_search_by_answer(std::vector<int>& pages, int n, int k) {
    int l = 0, r = pages[n - 1];
    while (l < r) {
        int mid = (l + r) / 2;
        if (check(pages, k, mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    return l;
}