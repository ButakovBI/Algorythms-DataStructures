#include <iostream>
#include <vector>

int main() {
    int n = 0;
    std::cin >> n;

    std::vector<int> vec(2 * n + 2);
    vec[0] = 1;
    vec[1] = 1;
    for (size_t i = 2; i <= n; i += 1) {
        if (i % 2) {
            vec[i] = vec[i / 2] - vec[i / 2 - 1];
        }
        else {
            vec[i] = vec[i / 2] + vec[i / 2 - 1];
        }
    }
    std::cout << vec[n];
}
