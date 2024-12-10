#include <iostream>
#include <vector>

int find_set(std::vector<int>& parent, std::vector<std::vector<int>>& size, int v);

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<int> parent(n + 1);
    std::vector<std::vector<int>> size(n + 1, std::vector<int>(1));

    for (int i = 1; i <= n; i += 1) {
        parent[i] = i;
        size[i][0] = i;
    }

    for (int i = 1; i < n; i += 1) {
        int x = 0, y = 0;
        std::cin >> x >> y;
        x = parent[x];
        y = parent[y];
        if (size[x].size() < size[y].size()) {
            std::swap(x, y);
        }

        for (int& elem : size[y]) {
            size[x].push_back(elem);
            parent[elem] = x;
        }
        size[y].clear();
    }

//    for (int i = 1; i <= n; i += 1) {
//        std::cout << find_set(parent, size, i) << ' ';
//    }
    for (auto& elem : size[parent[1]]) {
        std::cout << elem << ' ';
    }

    return 0;
}

int find_set(std::vector<int>& parent, std::vector<std::vector<int>>& size, int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent, size, parent[v]);
}