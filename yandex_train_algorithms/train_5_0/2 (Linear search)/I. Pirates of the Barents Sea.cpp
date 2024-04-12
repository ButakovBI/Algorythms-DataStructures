#include <algorithm>
#include <iostream>
#include <vector>
#include <numeric>

bool comp(std::pair<int, int>& coordinate1, std::pair<int, int>& coordinate2);

int needed_col = 0;

int main() {
    int n = 0;
    std::cin >> n;
    int x = 0, y = 0;
    std::vector<std::pair<int, int>> coordinates(n);
    std::vector<int> counter(n);
    int sum = 0;
    for (int i = 0; i < n; i += 1) {
        std::cin >> coordinates[i].first >> coordinates[i].second;
        counter[coordinates[i].first - 1]++;
        sum += coordinates[i].second;
    }
    needed_col = (sum + (n / 2)) / n;
//    std::cout << needed_col;
    std::sort(coordinates.begin(), coordinates.end(), comp);
//    for (auto elem : coordinates) {
//        std::cout << elem.first << ' ' << elem.second << '\n';
//    }
    int ans = 0;
    std::vector<bool> busy(n, false);
    for (int i = 0; i < n; i += 1) {
        if (!busy[coordinates[i].first - 1]) {
            busy[coordinates[i].first - 1] = true;
            counter[coordinates[i].first - 1]--;
            ans += std::abs(needed_col - coordinates[i].second);
        } else {
            int plus = 0;
            int cur_coord = coordinates[i].first - 1;
            if (cur_coord - std::accumulate(busy.begin(), busy.begin() + cur_coord, 0) - std::accumulate(counter.begin(), counter.begin() + cur_coord, 0) <= n - cur_coord + 1 - std::accumulate(busy.begin() + cur_coord, busy.end(), 0) - std::accumulate(counter.begin() + cur_coord, counter.end(), 0)) {
//                std::cout << "test " << cur_coord - std::accumulate(busy.begin(), busy.begin() + cur_coord, 0) - std::accumulate(counter.begin(), counter.begin() + cur_coord, 0) << ' ' << n - cur_coord - std::accumulate(busy.begin() + cur_coord, busy.end(), 0) - std::accumulate(counter.begin() + cur_coord, counter.end(), 0) << '\n';
                while (cur_coord + plus < n && busy[cur_coord + plus]) {
                    plus += 1;
                }
                if (cur_coord + plus < n && !busy[cur_coord + plus]) {
                    busy[cur_coord + plus] = true;
                    counter[cur_coord]--;
                    ans += plus + std::abs(needed_col - coordinates[i].second);
                } else {
                    plus = 0;
                    while (cur_coord - plus >= 0 && busy[cur_coord - plus]) {
                        plus += 1;
                    }
                    if (cur_coord - plus >= 0 && !busy[cur_coord - plus]) {
                        busy[cur_coord - plus] = true;
                        counter[cur_coord]--;
                        ans += plus + std::abs(needed_col - coordinates[i].second);
                    }
                }
            } else {
                while (cur_coord - plus >= 0 && busy[cur_coord - plus]) {
                    plus += 1;
                }
                if (cur_coord - plus >= 0 && !busy[cur_coord - plus]) {
                    busy[cur_coord - plus] = true;
                    counter[cur_coord]--;
                    ans += plus + std::abs(needed_col - coordinates[i].second);
                } else {
                    plus = 0;
                    while (cur_coord + plus < n && busy[cur_coord + plus]) {
                        plus += 1;
                    }
                    if (cur_coord + plus < n && !busy[cur_coord + plus]) {
                        busy[cur_coord + plus] = true;
                        counter[cur_coord]--;
                        ans += plus + std::abs(needed_col - coordinates[i].second);
                    }
                }
            }

        }
//        std::cout << ans << '\n';
    }
    std::cout << ans;

    return 0;
}

bool comp(std::pair<int, int>& coordinate1, std::pair<int, int>& coordinate2) {
    bool ans = false;
    if (std::abs(coordinate1.second - needed_col) < std::abs(coordinate2.second - needed_col)) {
        ans = true;
    } else if (std::abs(coordinate1.second - needed_col) == std::abs(coordinate2.second - needed_col)) {
        ans = coordinate1.first > coordinate2.first;
    }
    return ans;
}

//12
//1 1
//2 5
//1 6
//1 5
//6 4
//7 3
//7 4
//7 5
//8 11
//8 12
//11 11
//12 12