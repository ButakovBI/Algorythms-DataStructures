#include <iostream>
#include <vector>

int main() {
    int n = 0;
    std::cin >> n;

    std::vector<std::vector<int>> matrix(n, std::vector<int>(n));
    std::vector<bool> used(n + 1);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> matrix[i][j];
        }
    }
    int ans = 1e9;
    int first = 0, second = 0, third = 0;
    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < n; j += 1) {
            for (int k = 0; k < n; k += 1) {
                if (i != j && j != k && i != k && matrix[i][j] + matrix[j][k] + matrix[k][i] < ans) {
                    ans = matrix[i][j] + matrix[j][k] + matrix[k][i];
                    first = i + 1;
                    second = j + 1;
                    third = k + 1;
                }
            }
        }
    }
    std::cout << first << ' ' << second << ' ' << third;

    return 0;
}