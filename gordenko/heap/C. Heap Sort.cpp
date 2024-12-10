#include <iostream>
#include <vector>

void sift_up(std::vector<int>& arr, int idx);
void sift_down(std::vector<int>& arr, int idx, int n);
void heap_sort(std::vector<int>& arr, int n);

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<int> numbers(n);
    for (int i = 0; i < n; i += 1) {
        std::cin >> numbers[i];

    }
    heap_sort(numbers, n);
    for (int i = 0; i < n; i += 1) {
        std::cout << numbers[i] << ' ';
    }
    return 0;
}

void sift_up(std::vector<int>& arr, int idx) {
    while (idx > 0 && arr[idx] < arr[(idx - 1) / 2]) {
        std::swap(arr[idx], arr[(idx - 1) / 2]);
        idx = (idx - 1) / 2;
    }
}

void sift_down(std::vector<int>& arr, int idx, int n) {
    bool break_flag = false;
    while (!break_flag && idx * 2 + 1 < n) {
        int left = idx * 2 + 1, right = idx * 2 + 2;
        int cur_v = left;
        if (right < n && arr[right] > arr[left]) {
            cur_v = right;
        }
        if (arr[idx] > arr[cur_v]) {
            break_flag = true;
        } else {
            std::swap(arr[idx], arr[cur_v]);
            idx = cur_v;
        }
    }
}

void heap_sort(std::vector<int>& arr, int n) {
    for (int i = n / 2; i >= 0; i -= 1) {
        sift_down(arr, i, n);
    }
    for (int i = n - 1; i >= 0; i--) {
        std::swap(arr[0], arr[i]);
        sift_down(arr, 0, i);
    }
}