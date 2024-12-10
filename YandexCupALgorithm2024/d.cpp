#include <iostream>
#include <string>

int main() {
    long long left = 1, right = 16;
    std::string response;

    while (left + 1< right) {
        long long mid = left + (right - left) / 2;
        std::cout << mid << std::endl;
        std::cout.flush();

        std::cin >> response;
        if (response == "wet") {
            left = mid;
        } else if (response == "ok") {
            right = mid;
        } else if (response == "fail") {
            return 0;
        }
    }

    std::cout << "! " << left << std::endl;
    std::cout.flush();

    return 0;
}
