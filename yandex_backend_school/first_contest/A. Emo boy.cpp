#include <iostream>
#include <string>

int main() {
    std::string name = "";
    std::cin >> name;
    const int needed_size = 8;

    int size = 0;
    bool has_digit = false, has_high = false, has_low = false;

    for (const char& sym : name) {
        size++;
        if (!has_digit && std::isdigit(sym)) {
            has_digit = true;
        }
        if (!has_high && std::isupper(sym)) {
            has_high = true;
        }
        if (!has_low && std::islower(sym)) {
            has_low = true;
        }
    }

    std::string ans = "NO";
    if (size >= needed_size && has_digit && has_high && has_low) {
        ans = "YES";
    }

    std::cout << ans;

    return 0;
}
