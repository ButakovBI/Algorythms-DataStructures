#include <iostream>

int main() {
    int x = 0, y = 0, p = 0;
    std::cin >> x >> y >> p;
    int turn = 0;
    int soldiers = 0;
    int cur_attack;
    while (x > 0 && y > 0) {
        cur_attack = x;
        if (turn != 0) {
            soldiers += p;
        }
        if ((y <= x && 3 * (2 * x - p - y) > (p - x + y) * 2) || x <= p) {
            if (cur_attack > y) {
                cur_attack -= y;
                y = 0;
                soldiers -= cur_attack;
            } else {
                y -= cur_attack;
            }
        } else {
            if (cur_attack > soldiers) {
                cur_attack -= soldiers;
                soldiers = 0;
                y -= cur_attack;
            } else if (cur_attack != p) {
                soldiers -= cur_attack;
            }
        }
        x -= soldiers;
        turn += 1;
    }
    while (x > 0 && soldiers > 0) {
        soldiers -= x;
        x -= soldiers;
        turn += 1;
    }
    if (x <= 0) {
        turn = -1;
    }
    std::cout << turn;
    return 0;
}