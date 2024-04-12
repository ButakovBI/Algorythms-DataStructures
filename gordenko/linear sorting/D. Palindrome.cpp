#include <algorithm>
#include <iostream>
#include <vector>

void counting_sort(std::vector<char>& symbols, int size);

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<char> symbols(n);
    for (int i = 0; i < n; i += 1) {
        std::cin >> symbols[i];
    }
    counting_sort(symbols, n);

    return 0;
}

void counting_sort(std::vector<char>& symbols, int size) {
    std::vector<int> counter(26, 0);
    for (int i = 0; i < size; i += 1) {
        counter[symbols[i] - 'A'] += 1;
    }
    for (int i = 1; i < 26; i += 1) {
        counter[i] += counter[i - 1];
    }

    std::vector<char> sorted_symbols(size);
    for (int i = size - 1; i >= 0; i -= 1) {
        sorted_symbols[counter[symbols[i] - 'A']-- - 1] = symbols[i];
    }
//    for (int i = 0; i < size; i += 1) {
//        std::cout << sorted_symbols[i] << ' ';
//    }

    std::vector<char> ans(size, 0);
    int pos_ans = 0, ptr2 = -1;
    for (int i = 1; i < size; i += 1) {
        if (sorted_symbols[i] == sorted_symbols[i - 1]) {
            ans[pos_ans] = sorted_symbols[i];
            ans[size - pos_ans - 1] = sorted_symbols[i];
            pos_ans += 1;
        } else if (ptr2 == -1) {
            if (i == 1) {
                ptr2 = i - 1;
            } else {
                ptr2 = i;
            }

        }
    }
    if (ans[pos_ans] == 0) {
        ans[pos_ans] = sorted_symbols[ptr2];
    }

    for (int i = 0; i < size; i += 1) {
        if (ans[i] != 0) {
            std::cout << ans[i];
        }
    }
}
