#include <iostream>
#include <vector>

int find_set(std::vector<int>& parent, std::vector<int>& size, int v);
void union_sets(std::vector<int>& parent, std::vector<int>& size, int a, int b);

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<int> parent(n + 1);
    std::vector<int> size(n + 1);

    for (int i = 1; i <= n; i += 1) {
        parent[i] = i;
        size[i] = 1;
    }

    for (int i = 1; i <= n; i += 1) {
        int key = 0;
        std::cin >> key;
        union_sets(parent, size, i, key);
    }

    int ans = 0;
    for (int i = 1; i <= n; i += 1) {
        if (find_set(parent, size, i) == i) {
            ans += 1;
        }
    }

    std::cout << ans;

    return 0;
}

int find_set(std::vector<int>& parent, std::vector<int>& size, int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent, size, parent[v]);
}

void union_sets(std::vector<int>& parent, std::vector<int>& size, int a, int b) {
    a = find_set(parent, size, a);
    b = find_set(parent, size, b);
    if (a != b) {
        if (size[a] > size[b]) {
            std::swap(a, b);
        }
        parent[a] = b;
        size[b] += size[a];
    }
}