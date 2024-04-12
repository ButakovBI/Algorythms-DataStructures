#include <iostream>

void hanoi(int n, int from, int to, int tmp);

int main() {
    int n = 0;
    std::cin >> n;
    hanoi(n, 1, 3, 2);
    return 0;
}

void hanoi(int n, int from, int to, int tmp) {
    if (n == 0) {
        return;
    }
    hanoi(n - 1, from, tmp, to);
    std::cout << n << ' ' << from << ' ' << to << '\n';
    hanoi(n - 1, tmp, to, from);
}