#include <iostream>
#include <string>
#include <vector>

void sift_up(std::vector<int>& arr, int idx);
void sift_down(std::vector<int>& arr, int idx, int n);

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<int> numbers;
    std::string command;
    int insert_value = 0;
    int size = 0;
    for (int i = 0; i < n; i += 1) {
        std::cin >> command;
        if (command == "insert") {
            std::cin >> insert_value;
            numbers.push_back(insert_value);
            sift_up(numbers, size++);
        } else if (command == "getMin") {
            std::cout << numbers[0] << ' ';
        } else if (command == "extractMin") {
            std::cout << numbers[0] << ' ';
            numbers[0] = numbers.back();
            numbers.pop_back();
            sift_down(numbers, 0, --size);
        }
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
        if (right < n && arr[right] < arr[left]) {
            cur_v = right;
        }
        if (arr[idx] <= arr[cur_v]) {
            break_flag = true;
        } else {
            std::swap(arr[idx], arr[cur_v]);
            idx = cur_v;
        }
    }
}
