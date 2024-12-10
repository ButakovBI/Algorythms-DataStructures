#include <iostream>
#include <string>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::string symbols = "";
    std::cin >> symbols;
    int m = 0;
    std::cin >> m;
    int l = 0, r = 0;
    const int length = symbols.length();
    std::vector<int> prefix(length + 1);
    for (int i = 1; i <= length; i += 1) {
        if (i == 1) {
            prefix[i] = 1;
            continue;
        }
        if (symbols[i - 1] == symbols[i - 2]) {
            prefix[i] = prefix[i - 1] + 1;
        } else {
            prefix[i] = std::max(prefix[i - 1], 1);
        }

    }
//    for (int i = 0; i <= length; i += 1) {
//        std::cout << prefix[i] << ' ';
//    }
    for (int i = 0; i < m; i += 1) {
        std::cin >> l >> r;
        std::cout << prefix[r] - prefix[l] << '\n';
    }
    return 0;
}

/* Thu Mar 07 2024 18:59:30 GMT+0300 (Moscow Standard Time) */