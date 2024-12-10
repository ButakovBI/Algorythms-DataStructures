#include <iostream>
#include <vector>

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<int> vec(n + 3);
    vec[n] = 1;
    for (int i = n - 1; i >= 0; i -= 1) {
        vec[i] = vec[i + 1] + vec[i + 2] + vec[i + 3];
    }
    std::cout << vec[0] << std::endl;
}
