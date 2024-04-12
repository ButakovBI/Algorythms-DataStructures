#include <iostream>
#include <vector>

int binary_search_by_answer(const std::vector<int>& lengths, int n, int k, int max_element);
int check(const std::vector<int>& lengths, int n, int mid);

int main() {
    int n = 0, k = 0;
    std::cin >> n >> k;
    std::vector<int> lengths(n);
    int max_element = -1e7 - 1;
    int sum_elements = 0;
    for (int i = 0; i < n; i += 1) {
        std::cin >> lengths[i];
        if (lengths[i] > max_element) {
            max_element = lengths[i];
        }
        sum_elements += lengths[i];
    }
    int res = binary_search_by_answer(lengths, n, k, max_element);
    std::cout << res;
    return 0;
}

//15 10
//1 1 1 1 1 1 1 1 1 1 1 1 1 1 1

int check(const std::vector<int>& lengths, int n, int mid) {
    int count = 0;
    for (int i = 0; i < n; i += 1) {
        count += lengths[i] / mid;
    }
    return count;
}

int binary_search_by_answer(const std::vector<int>& lengths, int n, int k, int max_element) {
    int start = 1;
    int end = max_element;
    while (start <= end) {
        int mid = (start + end) / 2;
        int cur_k = check(lengths, n, mid);
        if (cur_k >= k) {
            start = mid + 1;
        } else {
            end = mid - 1;
        }
    }
    return end;
}