#include <iostream>
#include <vector>
#include <deque>

int main() {
    int n, k;
    std::cin >> n >> k;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    std::deque<int> deque;
    for (int i = 0; i < k; ++i) {
        deque.push_back(a[i]);
        while (deque.size() > 1 && deque.back() < deque[deque.size() - 2]) {
            deque.erase(deque.end() - 2);
        }
    }

    std::cout << deque.front() << std::endl;

    for (int i = k; i < n; ++i) {
        if (deque.front() == a[i - k] || deque.size() > k) {
            deque.pop_front();
        }
        deque.push_back(a[i]);
        while (deque.size() > 1 && deque.back() < deque[deque.size() - 2]) {
            deque.erase(deque.end() - 2);
        }
        std::cout << deque.front() << std::endl;
    }

    return 0;
}