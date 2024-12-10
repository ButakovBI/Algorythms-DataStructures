#include <iostream>
#include <vector>

void merge_sort(std::vector<int>& elements, int start, int end);
void merge(std::vector<int>& elements, int start, int mid, int end);

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<int> elements(n);
    for (int i = 0; i < n; i += 1) {
        std::cin >> elements[i];
    }
    merge_sort(elements, 0, n - 1);
    for (int& elem : elements) {
        std::cout << elem << ' ';
    }
    return 0;
}

void merge(std::vector<int>& elements, int start, int mid, int end) {
    int size1 = mid - start + 1, size2 = end - mid;
    std::vector<int> left(elements.begin() + start, elements.begin() + mid + 1);
    std::vector<int> right(elements.begin() + mid + 1, elements.begin() + end + 1);
    int i = 0, j = 0, k = start;
    while (i < size1 && j < size2) {
        if (left[i] < right[j]) {
            elements[k] = left[i];
            i++;
        } else {
            elements[k] = right[j];
            j++;
        }
        k++;
    }
    while (i < size1) {
        elements[k] = left[i];
        i++;
        k++;
    }
    while (j < size2) {
        elements[k] = right[j];
        j++;
        k++;
    }
}

void merge_sort(std::vector<int>& elements, int start, int end) {
    if (start >= end) {
        return;
    }
    int mid = (start + end) / 2;
    merge_sort(elements, start, mid);
    merge_sort(elements, mid + 1, end);
    merge(elements, start, mid, end);
}

//10
//3 7 4 -2 10 5 7 8 -1 2