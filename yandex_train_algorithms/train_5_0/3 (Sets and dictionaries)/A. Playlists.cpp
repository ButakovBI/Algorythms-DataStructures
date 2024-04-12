#include <iostream>
#include <map>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n = 0;
    std::cin >> n;
    int k = 0;
    std::map<std::string, int> tracks;
    std::string track;
    for (int i = 0; i < n; i += 1) {
        std::cin >> k;
        for (int j = 0; j < k; j += 1) {
            std::cin >> track;
            tracks[track]++;
        }
    }
    int cnt = 0;
    for (auto& elem : tracks) {
        if (elem.second == n) {
            cnt++;
        }
    }
    std::cout << cnt << '\n';
    for (auto& elem : tracks) {
        if (elem.second == n) {
            std::cout << elem.first << ' ';
        }
    }
    return 0;
}