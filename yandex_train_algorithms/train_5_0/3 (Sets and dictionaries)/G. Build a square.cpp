#include <cmath>
#include <iostream>
#include <set>
#include <vector>

double dist(int x1, int y1, int x2, int y2);

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::set<std::pair<int, int>> coordinates;
    int n = 0;
    std::cin >> n;
    for (int i = 0; i < n; i += 1) {
        int x = 0, y = 0;
        std::cin >> x >> y;
        coordinates.insert({x, y});
    }

    int max_elems = 1;
    std::vector<std::pair<int, int>> ans;

    for (auto& elem : coordinates) {
        for (auto& pair_elem : coordinates) {
            if (pair_elem != elem) {

                int diffY = std::abs(pair_elem.second - elem.second),
                    diffX = std::abs(pair_elem.first - elem.first);

                std::pair<int, int> elem1 = {pair_elem.first + diffY, pair_elem.second - diffX},
                                    elem2 = {pair_elem.first - diffY, pair_elem.second + diffX},
                                    elem3 = {elem.first - diffX, elem.second + diffY},
                                    elem4 = {elem.first + diffX, elem.second - diffY};
                std::vector<std::pair<std::pair<int, int>, bool>> found = {{elem1, false},
                                                                           {elem2, false},
                                                                           {elem3, false},
                                                                           {elem4, false}};
                for (auto& elem : found) {
                    std::cout << elem.first.first << ' ' << elem.first.second << '\n';
                }

                if (coordinates.find(elem1) != coordinates.end()) {
                    found[0].second = true;
                }
                if (coordinates.find(elem2) != coordinates.end()) {
                    found[1].second = true;
                }
                if (coordinates.find(elem3) != coordinates.end()) {
                    found[2].second = true;
                }
                if (coordinates.find(elem4) != coordinates.end()) {
                    found[3].second = true;
                }
                if ((found[0].second && found[1].second) || (found[2].second && found[3].second)) {
                    max_elems = 4;
                    ans.clear();
                    break;
                } else if (max_elems < 3 &&
                           (found[0].second || found[1].second || found[2].second || found[3].second)) {
                    ans.clear();
                    if (found[0].second) {
                        ans.push_back(found[1].first);
                    } else if (found[1].second) {
                        ans.push_back(found[0].first);
                    } else if (found[2].second) {
                        ans.push_back(found[3].first);
                    } else if (found[3].second) {
                        ans.push_back(found[2].first);
                    }
                    max_elems = 3;
                } else if (max_elems < 2) {
                    ans.clear();
                    max_elems = 2;
                    ans.push_back(found[0].first);
                    ans.push_back(found[1].first);
                }
            }
        }
    }
    std::pair<int, int> some_elem = *coordinates.end();
    if (max_elems == 1) {
        ans.push_back({some_elem.first + 1, some_elem.second});
        ans.push_back({some_elem.first, some_elem.second + 1});
        ans.push_back({some_elem.first + 1, some_elem.second + 1});
    }
    std::cout << 4 - max_elems << '\n';
    for (auto& elem : ans) {
        std::cout << elem.first << ' ' << elem.second << '\n';
    }

    return 0;
}

double dist(int x1, int y1, int x2, int y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}