#include <iostream>
#include <vector>

int partition(std::vector<int>& elements, int start, int end);
void quick_sort(std::vector<int>& elements, int start, int end, int& counter);

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<int> elements(n);
    for (int i = 0; i < n; i += 1) {
        std::cin >> elements[i];
    }
    int counter = 0;
    quick_sort(elements, 0, n - 1, counter);
    std::cout << counter << '\n';
    for (int& elem : elements) {
        std::cout << elem << ' ';
    }
    return 0;
}

int partition(std::vector<int>& elements, int start, int end) {
    int pivot = elements[end];
    int i = start - 1;
    for (int j = start; j <= end; j += 1) {
        if (elements[j] <= pivot) {
            i++;
            std::swap(elements[i], elements[j]);
        }
    }
    return i;
}

void quick_sort(std::vector<int>& elements, int start, int end, int& counter) {
    if (start >= end) {
        return;
    }
    int p = partition(elements, start, end);
    if (start < p - 1) {
        quick_sort(elements, start, p - 1, counter);
        counter++;
    }
    if (p + 1 < end) {
        quick_sort(elements, p + 1, end, counter);
        counter++;
    }
}