#include <iostream>

long long tree(long long n);

int main() {
    long long n = 0;
    std::cin >> n;
    std::cout << tree(n);
    return 0;
}

long long tree(long long n) {
    if (n == 0) {
        return 1;
    }
    return n * 2 + 2 + tree(n - 1);
}