#include <iostream>
#include <vector>

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; i += 1) {
        std::cin >> a[i];
    }

    int ans = a[0];
    int sum = 0;
    int min_sum = 0;
    int left = 0;
    int right = 0;
    int min_pos = -1;

    for (int i = 0; i < n; i += 1) {
        sum += a[i];

        int diff = sum - min_sum;
        if (diff > ans) {
            ans = diff;
            left = min_pos + 1;
            right = i;
        }
        if (sum < min_sum) {
            min_pos = i;
            min_sum = sum;
        }
    }
    std::cout << left + 1 << ' ' << right + 1 << ' ' << ans;
}