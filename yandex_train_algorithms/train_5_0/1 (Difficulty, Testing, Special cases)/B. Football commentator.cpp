#include <iostream>

int main() {
    int ans = 0;
    int goals_guest1 = 0, goals_guest2 = 0;
    int goals_a1 = 0, goals_b1 = 0, goals_a2 = 0, goals_b2 = 0;
    int home_or_guest = 0;
    char sym = 0;
    std::cin >> goals_a1 >> sym >> goals_b1 >> goals_a2 >> sym >> goals_b2 >> home_or_guest;
    if (home_or_guest == 2) {
        goals_guest1 += goals_a1;
        goals_guest2 += goals_b2;
    } else {
        goals_guest1 += goals_a2;
        goals_guest2 += goals_b1;
    }
    if (goals_a1 + goals_a2 <= goals_b2 + goals_b1) {
        ans += goals_b2 + goals_b1 - goals_a1 - goals_a2;
        if (home_or_guest == 2 && goals_guest1 <= goals_guest2
            || home_or_guest == 1 && goals_guest1 + ans <= goals_guest2) {
            ans += 1;
        }
    }
//    std::cout << goals_guest1 << goals_guest2;
//    if (goals_guest1 <= goals_guest2 && goals_a1 + goals_a2 == goals_b2 + goals_b1) {
//        ans = 1;
//    }
    std::cout << ans;
    return 0;
}