#include <iostream>
#include <vector>


int main() {
    int n = 0;
    std::cin >> n;
    for (int i = 0; i < n; i += 1) {
        int size = 0;
        std::cin >> size;
        std::vector<double> values(size);
        for (int j = 0; j < size; j += 1) {
            std::cin >> values[j];
        }

        int res = 1;
        bool break_flag = false;
        for (int idx = 0; idx < size - 2 && !break_flag; idx += 1) {
            if (values[idx + 2] < values[idx] && values[idx] < values[idx + 1]) {
                res = 0;
                break_flag = true;
            }
        }
        std::cout << res << '\n';
    }


    return 0;
}