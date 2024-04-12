#include <iostream>
#include <vector>

void build(std::vector<long long>& tree, int& size, int n);
void upd(std::vector<long long>& tree, int idx, int start, int end, int l, int r, int x);
long long query(std::vector<long long>& tree, int idx, int start, int end, int pos);

int main() {
    int n = 0, m = 0;
    std::cin >> n >> m;
    int size = 1;
    std::vector<long long> tree;
    build(tree, size, n);
    for (int i = 0; i < m; i += 1) {
        int command = 0;
        std::cin >> command;
        if (command == 1) {
            int l = 0, r = 0, x = 0;
            std::cin >> l >> r >> x;
            upd(tree, 1, 1, size, l, r, x);
//            for (auto& elem : tree) {
//                std::cout << elem << ' ';
//            }
//            std::cout << '\n';
        } else if (command == 2) {
            int idx = 0;
            std::cin >> idx;
            std::cout << query(tree, 1, 1, size, idx) << '\n';
        }
    }
}

void build(std::vector<long long>& tree, int& size, int n) {
    while (size < n) {
        size *= 2;
    }
    tree.assign(2 * size, 0);
}

void upd(std::vector<long long>& tree, int idx, int start, int end, int l, int r, int x) {
    if (start == l && end == r) {
        tree[idx] += x;
        return;
    }
    if (l > r) {
        return;
    }
    int mid = (start + end) / 2;
    if (l <= mid) {
        upd(tree, 2 * idx, start, mid, l, std::min(r, mid), x);
    }
    if (r >= mid + 1) {
        upd(tree, 2 * idx + 1, mid + 1, end, std::max(mid + 1, l), r, x);
    }
}

long long query(std::vector<long long>& tree, int idx, int start, int end, int pos) {
    if (start == end) {
        return tree[idx];
    }
    int mid = (start + end) / 2;
    if (pos <= mid) {
        return tree[idx] + query(tree, 2 * idx, start, mid, pos);
    } else {
        return tree[idx] + query(tree, 2 * idx + 1, mid + 1, end, pos);
    }
}