#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n = 0;
    std::cin >> n;

    const int size = 1e6 + 1;

    int ans = 0;

    std::vector<std::pair<int, size_t> > vec;
    vec.resize(size);

    vec[1].first = 0;

    for (size_t i = 2; i <= n; i += 1) {
        vec[i] = std::make_pair(vec[i - 1].first + 1, i - 1);
        if (i % 3 == 0) {
            if (vec[i / 3].first + 1 > vec[i].first) {
                vec[i] = std::make_pair(vec[i].first, vec[i].second);
            }
            else {
                vec[i] = std::make_pair(vec[i / 3].first + 1, i / 3);
            }
        }
        if (i % 2 == 0) {
            if (vec[i / 2].first + 1 > vec[i].first) {
                vec[i] = std::make_pair(vec[i].first, vec[i].second);
            }
            else {
                vec[i] = std::make_pair(vec[i / 2].first + 1, i / 2);
            }
        }

    }

    std::cout << vec[n].first << std::endl;

    std::vector<int> ans_vec;

    std::pair<int, size_t> param = vec[n];

    while (param.second != 0) {
        ans_vec.push_back(param.second);
        param = vec[param.second];
    }

    std::reverse(ans_vec.begin(), ans_vec.end());
    for (auto& elem : ans_vec) {
        std::cout << elem << ' ';
    }

    std::cout << n << ' ';

}
