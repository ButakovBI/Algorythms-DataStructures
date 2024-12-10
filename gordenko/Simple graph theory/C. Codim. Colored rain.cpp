#include <iostream>
#include <vector>

int main() {
    int n = 0;
    std::cin >> n;

    std::vector<std::vector<int>> matrix(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> matrix[i][j];
        }
    }

    std::vector<int> colors(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> colors[i];
    }

    int badBridges = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (matrix[i][j] && colors[i] != colors[j]) {
                badBridges++;
            }
        }
    }

    std::cout << badBridges << '\n';

    return 0;
}