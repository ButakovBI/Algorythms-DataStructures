#include <iostream>
#include <vector>

int main() {
    int t = 0;
    std::cin >> t;

    for (int i = 0; i < t; i += 1) {
        int n = 0;
        std::cin >> n;
        int cur_value = 0;
        std::vector<int> ans;
        int count = 0;
        int min_value = 1e6;
        int cur_length = 0;
        for (int j = 0; j < n; j += 1) {
            std::cin >> cur_value;

            if (min_value > cur_value) {
                min_value = cur_value;
            }
            if (min_value <= cur_length) {
                ans.push_back(cur_length);
                cur_length = 0;
                count++;
                min_value = cur_value;
            }
            cur_length++;
        }
        if (cur_length > 0) {
            count++;
            ans.push_back(cur_length);
        }
        std::cout << count << '\n';
        for (int elem : ans) {
            std::cout << elem << ' ';
        }
        std::cout << '\n';

    }

    return 0;
}