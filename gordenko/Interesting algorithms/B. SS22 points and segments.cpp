#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    int n = 0, m = 0;
    std::cin >> n >> m;

    std::vector<std::pair<int, int>> lengths(n);
    for (int i = 0; i < n; i += 1) {
        std::cin >> lengths[i].first >> lengths[i].second;
    }
    std::sort(lengths.begin(), lengths.end());
//    for (auto& elem : lengths) {
//        std::cout << elem.first << ' ' << elem.second << '\n';
//    }
    std::vector<int> points(m);
    for (int i = 0; i < m; i += 1) {
        std::cin >> points[i];
    }


    for (int i = 0; i < m; i += 1) {
        int cnt = 0;
        int ptr = 0;
        while (ptr < n && lengths[ptr].first <= points[i]) {
            if (lengths[ptr].second >= points[i]) {
                cnt++;
            }
            ptr++;
        }
        std::cout << cnt << ' ';
    }
    return 0;
}