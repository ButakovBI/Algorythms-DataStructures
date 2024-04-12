#include <iostream>
#include <vector>

void build(std::vector<long long>& tree, int& size, int n);
void upd(std::vector<long long>& tree, std::vector<long long>& lazy, int idx, int start, int end, int l, int r, int x);
void push(std::vector<long long>& tree, std::vector<long long>& lazy, int idx, int start, int end);
long long query(std::vector<long long>& tree, int idx, int start, int end, int l, int r);

int main() {
    int n = 0, q = 0;
    std::cin >> n >> q;
    std::vector<long long> tree;
    int size = 1;
    build(tree, size, n);
    std::vector<long long> lazy(2 * size);
    for (int i = 0; i < q; i += 1) {
        int command = 0;
        std::cin >> command;
        if (command == 1) {
            int l = 0, r = 0, x = 0;
            std::cin >> l >> r >> x;
            upd(tree, lazy, 1, 1, size, l, r, x);
        } else if (command == 2) {
            int l = 0, r = 0;
            std::cin >> l >> r;
            std::cout << query(tree, 1, 1, size, l, r) << '\n';
        }
//        for (auto& elem : tree) {
//            std::cout << elem << ' ';
//        }
//        std::cout << '\n';
    }

    return 0;
}

void build(std::vector<long long>& tree, int& size, int n) {
    while (size < n) {
        size *= 2;
    }
    tree.assign(2 * size, 0);
}

void push(std::vector<long long>& tree, std::vector<long long>& lazy, int idx, int start, int end) {
    if (lazy[idx] != 0) {
        tree[idx] += lazy[idx] * (end - start + 1);
        if (start != end) {
            lazy[2 * idx] += lazy[idx];
            lazy[2 * idx + 1] += lazy[idx];
        }
        lazy[idx] = 0;
    }
}

void upd(std::vector<long long>& tree, std::vector<long long>& lazy, int idx, int start, int end, int l, int r, int x) {
    push(tree, lazy, idx, start, end);
    if (l > r) {
        return;
    }
    if (start == l && end == r) {
        lazy[idx] += x;
        push(tree, lazy, idx, start, end);
        return;
    }
    int mid = (start + end) / 2;
    upd(tree, lazy, 2 * idx, start, mid, l, std::min(r, mid), x);
    upd(tree, lazy, 2 * idx + 1, mid + 1, end, std::max(l, mid + 1), r, x);
    tree[idx] = tree[2 * idx] + tree[2 * idx + 1];
}

long long query(std::vector<long long>& tree, int idx, int start, int end, int l, int r) {
    if (start == l && end == r) {
        return tree[idx];
    }
    if (l > r) {
        return 0;
    }
    int mid = (start + end) / 2;
    long long ans = 0;
    if (l <= mid) {
        ans += query(tree, 2 * idx, start, mid, l, std::min(r, mid));
    }
    if (r >= mid + 1) {
        ans += query(tree, 2 * idx + 1, mid + 1, end, std::max(l, mid + 1), r);
    }
    return ans;
}