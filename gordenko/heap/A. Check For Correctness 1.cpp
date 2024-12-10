#include <iostream>
#include <vector>

void sift_up(std::vector<long long>& arr, int idx);
void sift_down(std::vector<long long>& arr, int idx, int n, bool& flag);

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<long long> numbers(n + 1);
    bool flag = true;
    for (int i = 1; i <= n; i += 1) {
        std::cin >> numbers[i];
    }
    for (int i = n; flag && i > 0; i -= 1) {
        sift_down(numbers, i, n, flag);
    }
    std::cout << (flag ? "YES" : "NO");
    return 0;
}

void sift_up(std::vector<long long>& arr, int idx) {
    while (idx > 1 && arr[idx] < arr[idx / 2]) {
        std::swap(arr[idx], arr[idx / 2]);
        idx /= 2;
    }
}

void sift_down(std::vector<long long>& arr, int idx, int n, bool& flag) {
    bool break_flag = false;
    while (!break_flag && idx * 2 <= n) {
        int left = idx * 2, right = idx * 2 + 1;
        int cur_v = (right <= n && arr[right] < arr[left] ? right : left);
        if (arr[idx] <= arr[cur_v]) {
            break_flag = true;
        } else {
            std::swap(arr[idx], arr[cur_v]);
            idx = cur_v;
            flag = false;
        }
    }
}
