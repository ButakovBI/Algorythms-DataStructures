#include <iostream>
#include <vector>

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<int> in(n), out(n);
    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < n; j += 1) {
            int value = 0;
            std::cin >> value;
            in[j] += value;
            out[i] += value;
        }
    }
    for (int i = 0; i < n; i += 1) {
        std::cout << in[i] << '\n' << out[i] << '\n';
    }

    return 0;
}