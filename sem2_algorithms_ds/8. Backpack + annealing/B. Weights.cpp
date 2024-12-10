#include <iostream>
#include <bitset>

int main() {
    std::bitset<10001> w = 1;
    int n = 0, summ = 0;
    std::cin >> n;
    for (int i = 0; i < n; i += 1) {
        int x = 0;
        std::cin >> x;
        w = w | (w << x);
        summ += x;
        //std::cout << w << std::endl;
    }
    if (summ % 2 == 0 && w[summ / 2]) {
        std::cout << "YES";
    }
    else {
        std::cout << "NO";
    }
}