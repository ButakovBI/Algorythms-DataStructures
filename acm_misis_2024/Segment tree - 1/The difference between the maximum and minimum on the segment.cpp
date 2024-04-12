#include <iostream>
#include <vector>

void build(std::vector<int>& tree, int& size, int n);
void upd(std::vector<int>& tree, int idx, int x, bool option);
long long query(std::vector<int>& tree, int idx, int start, int end, int l, int r, bool option);

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n = 0, m = 0;
    std::cin >> n >> m;
    std::vector<int> max_tree;
    std::vector<int> min_tree;
    int size = 1;
    build(max_tree, size, n);
    min_tree.assign(size * 2, 0);
    for (int i = 0; i < m; i += 1) {
        int command = 0;
        std::cin >> command;
        if (command == 1) {
            int l = 0, r = 0;
            std::cin >> l >> r;
            std::cout << query(max_tree, 1, 1, size, l, r, true)
            - query(min_tree, 1, 1, size, l, r, false) << '\n';
        } else if (command == 2) {
            int idx = 0, x = 0;
            std::cin >> idx >> x;
            upd(max_tree, idx + size - 1, x,true);
            upd(min_tree, idx + size - 1, x,false);
//            for (auto& elem : max_tree) {
//                std::cout << elem << ' ';
//            }
//            std::cout << '\n';
        }
    }

    return 0;
}

void build(std::vector<int>& tree, int& size, int n) {
    while (size < n) {
        size *= 2;
    }
    tree.assign(2 * size, 0);
}

void upd(std::vector<int>& tree, int idx, int x, bool option) {
    tree[idx] = x;
    for (int i = idx / 2; i > 0; i /= 2) {
        if (option) {
            tree[i] = std::max(tree[2 * i], tree[2 * i + 1]);
        } else {
            tree[i] = std::min(tree[2 * i], tree[2 * i + 1]);
        }
    }
}

long long query(std::vector<int>& tree, int idx, int start, int end, int l, int r, bool option) {
    if (start == l && end == r) {
        return tree[idx];
    }
    if (l > r) {
        return option ? -1e9 : 1e9;
    }
    int mid = (start + end) / 2;
    long long res = 1e9;
    if (option) {
        res = -1e9;
    }
    if (l <= mid) {
        if (option) {
            res = std::max(res, query(tree, 2 * idx, start, mid, l, std::min(r, mid), option));
        } else {
            res = std::min(res, query(tree, 2 * idx, start, mid, l, std::min(r, mid), option));
        }
    }
    if (r >= mid + 1) {
        if (option) {
            res = std::max(res, query(tree, 2 * idx + 1, mid + 1, end, std::max(l, mid + 1), r, option));
        } else {
            res = std::min(res, query(tree, 2 * idx + 1, mid + 1, end, std::max(l, mid + 1), r, option));
        }
    }
    return res;
}