#include <iostream>
#include <vector>

void partition(int a[], int l, int r, int& i, int& j)
{
    i = l - 1, j = r;
    int p = l - 1, q = r;
    int v = a[r];

    while (true) {
        while (a[++i] < v)
            ;

        while (v < a[--j])
            if (j == l)
                break;

        if (i >= j)
            break;

        std::swap(a[i], a[j]);

        if (a[i] == v) {
            p++;
            std::swap(a[p], a[i]);
        }

        if (a[j] == v) {
            q--;
            std::swap(a[j], a[q]);
        }
    }

    std::swap(a[i], a[r]);

    j = i - 1;
    for (int k = l; k < p; k++, j--)
        std::swap(a[k], a[j]);

    i = i + 1;
    for (int k = r - 1; k > q; k--, i++)
        std::swap(a[i], a[k]);
}


void quicksort(int a[], int l, int r)
{
    if (r <= l)
        return;

    int i, j;

    partition(a, l, r, i, j);

    quicksort(a, l, j);
    quicksort(a, i, r);
}


int main()
{
    int n;
    std::cin >> n;
    std::vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
    bool is_sorted = true;
    for (int i = 1; i < n; ++i) {
        if (arr[i] < arr[i - 1]) {
            is_sorted = false;
            break;
        }
    }
    if (is_sorted) {
        for (int i = 0; i < n; ++i) {
            std::cout << arr[i] << ' ';
        }
    }
    else {
        quicksort(&arr[0], 0, n - 1);
        for (int i = 0; i < n; ++i) {
            std::cout << arr[i] << ' ';
        }
    }
    return 0;
}