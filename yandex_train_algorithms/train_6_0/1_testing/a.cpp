#include <iostream>
#include <string>

int main() {
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0, x = 0, y = 0;
    std::cin >> x1 >> y1 >> x2 >> y2 >> x >> y;

    std::string direction;

    if (x < x1 && y > y2) {
        direction = "NW";
    } else if (x > x2 && y > y2) {
        direction = "NE";
    } else if (x < x1 && y < y1) {
        direction = "SW";
    } else if (x > x2 && y < y1) {
        direction = "SE";
    } else if (x < x1) {
        direction = "W";
    } else if (x > x2) {
        direction = "E";
    } else if (y > y2) {
        direction = "N";
    } else if (y < y1) {
        direction = "S";
    }

    std::cout << direction;

    return 0;
}
