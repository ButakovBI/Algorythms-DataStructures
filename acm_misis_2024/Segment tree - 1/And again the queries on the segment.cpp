#include <iostream>
#include <vector>

void build(std::vector<int>& values, std::vector<int>& tree, int& size, int n);
int query(std::vector<int>& tree, int idx, int start, int end, int l, int r, int x);

bool flag = false;

int main() {
    int n = 0, m = 0;
    std::cin >> n;
    std::vector<int> values(n);
    for (int i = 0; i < n; i += 1) {
        std::cin >> values[i];
    }
    int size = 1;
    std::vector<int> tree;
    build(values, tree, size, n);
    std::cin >> m;
    for (int i = 0; i < m; i += 1) {
        flag = false;
        int l = 0, r = 0, x = 0;
        std::cin >> l >> r >> x;
        for (auto& elem : tree) {
            std::cout << elem << ' ';
        }
        std::cout << '\n';
        int res = query(tree, 1, 1, size, l, r, x);
        std::cout << '\n' << res << '\n';
        if (res > x || res <= 0) {
            std::cout << -1 << '\n';
        } else {
            std::cout << res << '\n';
        }
    }
}

void build(std::vector<int>& values, std::vector<int>& tree, int& size, int n) {
    while (size < n) {
        size *= 2;
    }
    tree.assign(2 * size, 0);
    for (int i = 0; i < n; i += 1) {
        tree[size + i] = values[i];
    }
    for (int i = size - 1; i > 0; i -= 1) {
        tree[i] = std::max(tree[2 * i], tree[2 * i + 1]);
    }
}

int query(std::vector<int>& tree, int idx, int start, int end, int l, int r, int x) {
    if (l <= start && end <= r) {
        return tree[idx];
    }
    if (l > r) {
        return -1;
    }
    int mid = (start + end) / 2;
    int ans = -1;
    int res1 = 0, res2 = 0;
    if (l <= mid && tree[idx] > x) {
        res1 = query(tree, 2 * idx, start, mid, l, r, x);
        if (res1 <= x) {
            ans = std::max(ans, res1);
        }
    }
    if (r >= mid + 1 && tree[idx] > x) {
        res2 = query(tree, 2 * idx + 1, mid + 1, end, l, r, x);
        if (res2 <= x) {
            ans = std::max(ans, res2);
        }
    }
    return ans;
}