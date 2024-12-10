#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

int main() {

    int n = 0, k = 0;
    std::cin >> n >> k;

    std::vector<int> attractions(n);
    for (int i = 0; i < n; i += 1) {
        std::cin >> attractions[i];
    }
    
    std::vector<int> sorted_attractions(attractions.begin(), attractions.end());
    std::sort(sorted_attractions.begin(), sorted_attractions.end());

    std::unordered_map<int, int> attr_values;
    int part_sum = 0;
    for (int i = 0; i <= k; i += 1) {
        part_sum += sorted_attractions[i];
    }
    int start = 0, end = k;
    for (int i = 0; i < n; i += 1) {
        if (!attr_values[sorted_attractions[i]]) {
            while (end < n && sorted_attractions[i] - sorted_attractions[start] > sorted_attractions[end] - sorted_attractions[i]) {
                part_sum -= sorted_attractions[start];
                start += 1;
                end += 1;
                part_sum += sorted_attractions[end];
            }
            attr_values[sorted_attractions[i]] = part_sum;
        }
    }

    for (int i = 0; i < n; i += 1) {
        std::cout << attr_values[attractions[i]] << ' '
    }
    
    return 0;
}
