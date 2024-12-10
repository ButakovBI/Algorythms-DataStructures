#include <iostream>
#include <vector>


long long count_hills(const std::vector<int>& heights) {
    int n = heights.size();
    long long total_count = 0;
    int i = 1;

    while (i < n - 1) {
        if (heights[i] > heights[i - 1] && heights[i] > heights[i + 1]) {
            int l = i - 1;
            int r = i + 1;

            while (l > 0 && heights[l] > heights[l - 1]) {
                --l;
            }
            int up_len = i - l;

            while (r < n - 1 && heights[r] > heights[r + 1]) {
                ++r;
            }
            int down_len = r - i;

            total_count += up_len * down_len;

            i = r;
        } else {
            ++i;
        }
    }

    return total_count;
}

int main() {
    int t = 0;
    std::cin >> t;
    for (int i = 0; i < t; i += 1) {
        int n = 0;
        std::cin >> n;
        std::vector<int> heights(n);
        for (int j = 0; j < n; j += 1) {
            std::cin >> heights[j];
        }

        std::cout << count_hills(heights) << '\n';
    }

    return 0;
}
