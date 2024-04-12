#include <iostream>
#include <iterator>
#include <deque>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n = 0;
    std::cin >> n;

    std::deque<int> dq;

    for (int i = 0; i < n; ++i) {
        char sym = 0;
        std::cin >> sym;
        switch (sym) {
        case '+': {
            int num = 0;
            std::cin >> num;
            dq.push_back(num);
            break;
        }
        case '-': {
            std::cout << dq.front() << std::endl;;
            dq.pop_front();
            break;
        }
        case '*': {
            int num = 0;
            std::cin >> num;
            std::deque<int>::iterator a = dq.begin() + (dq.size() / 2) + (dq.size() % 2);
            dq.insert(a, num);
            break;
        }
        default: 0; break;
        }
    }
}