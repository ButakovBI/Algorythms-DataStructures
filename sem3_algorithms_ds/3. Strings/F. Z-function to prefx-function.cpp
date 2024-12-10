#include <iostream>
#include <vector>


int main() {
    int n = 0;
    std::cin >> n;
    std::vector<int> z(n);
    for(int i = 0; i < n; ++i){
        std::cin >> z[i];
    }
    std::vector<int> prefix_function(n, 0);
    for (int i = 1; i < z.size(); ++i) {
        for (int j = z[i] - 1; j >= 0; --j) {
            if (prefix_function[i + j] > 0) {
                break;
            }
            else {
                prefix_function[i + j] = j + 1;
            }
        }
    }

    for (auto& x : prefix_function) {
        std::cout << x << " ";
    }
}