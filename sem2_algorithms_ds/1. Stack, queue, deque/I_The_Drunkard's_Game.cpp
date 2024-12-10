#include <iostream>
#include <deque>

int main() {
    std::deque<int> q1;
    std::deque<int> q2;

    const int n = 5;

    int sym = 0;
    for (int i = 0; i < n; ++i) {
        std::cin >> sym;
        q1.push_back(sym);
    }

    for (int i = 0; i < n; ++i) {
        std::cin >> sym;
        q2.push_back(sym);
    }

    int cnt = 0;

    while ((!q1.empty()) && (!q2.empty())) {
        int card1 = q1.front();
        int card2 = q2.front();
        if ((card1 > card2) && (!(card2 == 0 && card1 == 9)) || ((card1 == 0 && card2 == 9))) {
            q1.push_back(card1);
            q1.push_back(card2);
        }
        else {
            q2.push_back(card1);
            q2.push_back(card2);
        }

        q1.pop_front();
        q2.pop_front();
        ++cnt;
        if (cnt > 1000000) {
            std::cout << "botva";
            return 0;
        }
    }

    if (q1.empty()) {
        std::cout << "second" << ' ' << cnt;
    }
    else {
        std::cout << "first" << ' ' << cnt;
    }

}