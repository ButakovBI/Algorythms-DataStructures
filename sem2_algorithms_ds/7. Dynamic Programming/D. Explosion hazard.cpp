#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n = 0;
    std::cin >> n;

    std::vector<int> vec(21);
    vec[1] = 2;
    vec[2] = 3;
    for (int i = 3; i <= 20; i += 1) {
        vec[i] = vec[i - 1] + vec[i - 2];
    }

    std::cout << vec[n];
}
