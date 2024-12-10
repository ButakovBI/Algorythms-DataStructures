#include <iostream>
#include <vector>
#include <deque>

int main() {
    int n = 0, k = 0;
    std::cin >> n >> k;

    std::vector<int> prices(n);
    for (int i = 0; i < n; i += 1) {
        std::cin >> prices[i];
    }

    long long cash = 0;
    std::vector<int> pay_day(n);

    std::deque<std::pair<int, int>> window;
    for (int i = 0; i < k && i < n; ++i) {
        window.push_back({prices[i], i});
        while (window.size() > 1 && window.back().first < window[window.size() - 2].first) {
            window.erase(window.end() - 2);
        }
        if (!window.empty()) {
            cash += window.front().first;
            pay_day[window.front().second]++;
        }
    }


    for (int i = k; i < n; ++i) {
        if (window.front().first == prices[i - k] || window.size() > k) {
            window.pop_front();
        }
        window.push_back({prices[i], i});
        while (window.size() > 1 && window.back().first < window[window.size() - 2].first) {
            window.erase(window.end() - 2);
        }
//        std::cout << window.front().fir << std::endl;
        cash += window.front().first;
        pay_day[window.front().second]++;
    }


    std::cout << cash << '\n';
    for (int i = 0; i < n; i += 1) {

        std::cout << pay_day[i] << ' ';
    }

    return 0;
}
