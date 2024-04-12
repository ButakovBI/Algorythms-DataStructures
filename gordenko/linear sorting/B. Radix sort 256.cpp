#include <climits>
#include <iostream>
#include <vector>

void radix_sort(std::vector<int>& numbers, std::vector<int>& tmp_digit, int size, int max_element);
void counting_sort(std::vector<int>& numbers, std::vector<int>& tmp_digit, int size, int exp);

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<int> numbers(n);
    std::vector<int> tmp_digit(n);
    int max_element = INT_MIN;
    for (int i = 0; i < n; i += 1) {
        std::cin >> numbers[i];
        if (numbers[i] > max_element) {
            max_element = numbers[i];
        }
    }

    radix_sort(numbers, tmp_digit, n, max_element);

    for (int i = 0; i < n; i += 1) {
        if (i == n - 1) {
            std::cout << numbers[i];
        } else {
            std::cout << numbers[i] << ' ';
        }
    }
    return 0;
}

void radix_sort(std::vector<int>& numbers, std::vector<int>& tmp_digit, int size, int max_element) {
    for (int i = 1; max_element / i > 0; i *= 8) {
        counting_sort(numbers, tmp_digit, size, i);
    }
}

void counting_sort(std::vector<int>& numbers, std::vector<int>& tmp_digit, int size, int exp) {
    std::vector<int> counter(256, 0);
    for (int i = 0; i < size; i += 1) {
        counter[numbers[i] / exp & 255]++;
    }

    for (int i = 1; i < 256; i += 1) {
        counter[i] += counter[i - 1];
    }

    for (int i = size - 1; i >= 0; i -= 1) {
        tmp_digit[counter[numbers[i] / exp & 255]-- - 1] = numbers[i];
    }

    for (int i = 0; i < size; i += 1) {
        numbers[i] = tmp_digit[i];
    }
}