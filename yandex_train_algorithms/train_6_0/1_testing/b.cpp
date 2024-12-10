#include <iostream>

int main() {
    long long A = 0, B = 0, C = 0, D = 0;
    std::cin >> A >> B >> C >> D;

    long long AB_max = std::max(A, B);
    long long CD_max = std::max(C, D);

    if (A + C >= B + D && B + D <= std::min(AB_max, CD_max)) {
        std::cout << B + 1 << " " << D + 1;
    }
    else if (B + D >= A + C && A + C <= std::min(AB_max, CD_max)) {
        std::cout << A + 1 << " " << C + 1;
    }
    else if (AB_max >= CD_max) {
        std::cout << AB_max + 1 << " 1";
    }
    else {
        std::cout << "1 " << CD_max + 1;
    }

    return 0;
}
