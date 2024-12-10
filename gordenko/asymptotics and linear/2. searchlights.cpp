#include <iostream>

int main() {

    int a = 0, b = 0, c = 0;
    int ans = 0;
    std::cin >> a >> b >> c;
    int min = a;
    if (b / 2 < min) {
        min = b / 2;
    }
    if (c < min) {
        min = c;
    }
    if (min > 0) {
        min -= 1;
    }
    ans = min * 4;
    a -= min;
    b -= min * 2;
    c -= min;
    while (true) {
        if (a > 0) {
            a -= 1;
            ans += 1;
        } else {
            break;
        }
        if (b > 0) {
            b -= 1;
            ans += 1;
        } else {
            break;
        }
        if (c > 0) {
            c -= 1;
            ans += 1;
        } else {
            break;
        }
        if (b > 0) {
            b -= 1;
            ans += 1;
        } else {
            break;
        }
    }
    std::cout << ans;
    return 0;
}