#include <iostream>
#include <string>

int main() {
    int n = 0;
    std::cin >> n;
    long long cur_number = 0;
    std::string ans(n - 1, '+');
    std::cin >> cur_number;
    long long last_digit = cur_number % 2;
    for (int i = 1; i < n; i += 1) {
        std::cin >> cur_number;
        if ((last_digit && cur_number % 2 == 0) || (last_digit == 0 && cur_number % 2)) {
            last_digit = (last_digit + cur_number) % 2;
        } else {
            ans[i - 1] = 'x';
        }
//        std::cout << last_digit << '\n';
    }
    std::cout << ans;
    return 0;
}