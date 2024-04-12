#include <iostream>
#include <vector>

int partition(std::vector<int>& elements, int start, int end);
void search(const std::vector<int>& red, const std::vector<int>& green, const std::vector<int>& blue,
            int nr, int ng, int nb);
void quick_sort(std::vector<int>& elements, int start, int end);
void update(int& ansR, int& ansG, int& ansB, int red, int green, int blue);
long long weight(long long a, long long b, long long c);

int main() {
    int t = 0;
    std::cin >> t;
    int nr = 0, ng = 0, nb = 0;
    for (size_t i = 0; i < t; i += 1) {
        std::cin >> nr >> ng >> nb;

        std::vector<int> red(nr);
        std::vector<int> green(ng);
        std::vector<int> blue(nb);

        for (size_t j = 0; j < nr; j += 1) {
            std::cin >> red[j];
        }
        for (size_t j = 0; j < ng; j += 1) {
            std::cin >> green[j];
        }
        for (size_t j = 0; j < nb; j += 1) {
            std::cin >> blue[j];
        }

        quick_sort(red, 0, nr - 1);
        quick_sort(green, 0, ng - 1);
        quick_sort(blue, 0, nb - 1);
        search(red, green, blue, nr, ng, nb);
    }

    return 0;
}

long long weight(long long a, long long b, long long c) {
    return (a - b) * (a - b) + (b - c) * (b - c) + (a - c) * (a - c);
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

void update(int& ansR, int& ansG, int& ansB, int red, int green, int blue) {
    ansR = red;
    ansG = green;
    ansB = blue;
}

void search(const std::vector<int>& red, const std::vector<int>& green, const std::vector<int>& blue,
            const int nr, const int ng, const int nb) {

    int i = 0, j = 0, k = 0;
    int ansR = red[0], ansG = green[0], ansB = blue[0];
    long long min_weight = weight(red[i], green[j], blue[k]);

    while (i < nr && j < ng && k < nb) {

        if (weight(red[i], green[j], blue[k]) < min_weight) {
            min_weight = weight(red[i], green[j], blue[k]);
            update(ansR, ansG, ansB, red[i], green[j], blue[k]);
        }
        long long weight1 = 1e18, weight2 = 1e18, weight3 = 1e18;
        bool flag = false;

        if (i + 1 < nr) {
            weight1 = weight(red[i + 1], green[j], blue[k]);
            if (weight1 < min_weight) {
                flag = true;
                min_weight = weight1;
                i++;
                update(ansR, ansG, ansB, red[i], green[j], blue[k]);
            }
        }

        if (j + 1 < ng) {
            weight2 = weight(red[i], green[j + 1], blue[k]);
            if (weight2 < min_weight) {
                flag = true;
                min_weight = weight2;
                j++;
                update(ansR, ansG, ansB, red[i], green[j], blue[k]);
            }
        }

        if (k + 1 < nb) {
            weight3 = weight(red[i], green[j], blue[k + 1]);
            if (weight3 < min_weight) {
                flag = true;
                min_weight = weight3;
                k++;
                update(ansR, ansG, ansB, red[i], green[j], blue[k]);
            }
        }

        if (!flag) {
            long long cur_min = std::min(std::min(weight1, weight2), weight3);
            if (weight1 == cur_min) {
                i++;
            } else if (weight2 == cur_min) {
                j++;
            } else {
                k++;
            }
        }

    }
    std::cout << ansR << ' ' << ansG << ' ' << ansB << '\n';
}