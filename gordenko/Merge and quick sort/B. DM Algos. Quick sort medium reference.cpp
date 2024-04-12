#include <iostream>
#include <vector>

int partition(std::vector<int>& elements, int start, int end);
void quick_sort(std::vector<int>& elements, int start, int end);

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<int> elements(n);
    for (int i = 0; i < n; i += 1) {
        std::cin >> elements[i];
    }
    quick_sort(elements, 0, n - 1);
    for (int& elem : elements) {
        std::cout << elem << ' ';
    }
    return 0;
}

int partition(std::vector<int>& elements, int start, int end) {
    int pivot = elements[(start + end) / 2];
    int i = start, j = end;
    while (i <= j) {

        while (elements[i] < pivot) {
            i++;
        }

        while (elements[j] > pivot) {
            j--;
        }

        if (i <= j) {
            std::swap(elements[i++], elements[j--]);
        }
    }
    return i;
}

void quick_sort(std::vector<int>& elements, int start, int end) {
    if (start >= end) {
        return;
    }
    int p = partition(elements, start, end);
    quick_sort(elements, start, p - 1);
    quick_sort(elements, p, end);
}