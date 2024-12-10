#include<iostream>
#include<vector>
#include<algorithm>
#include<random>
#include<string>

std::mt19937 rd;

int last = 0;

struct Node {
    int key = 0;
    int p = rd(), size = 1;

    int idx = 0;

    Node* first_zero = nullptr;

    Node* left = nullptr, * right = nullptr;
    Node(int key, int idx) : key(key), idx(idx) {
        if (key == 0) {
            first_zero = this;
        }
    }
    ~Node() = default;
};

int size_of(Node* node) {
    return node ? node->size : 0;
}

Node* first_zero_of(Node* root) {
    return root ? root->first_zero : nullptr;
}

void upd(Node* root) {
    root->size = 1 + size_of(root->left) + size_of(root->right);
    if (first_zero_of(root->left)) {
        root->first_zero = root->left;
    }
    else if (root->key == 0) {
        root->first_zero = root;
    }
    else if (first_zero_of(root->right)) {
        root->first_zero = root->right;
    }
    else {
        root->first_zero = nullptr;
    }
}

std::pair<Node*, Node*> split(Node* root, int sz) {
    if (!root) return { nullptr, nullptr };
    if (size_of(root->left) < sz) {
        std::pair<Node*, Node*> q = split(root->right, sz - size_of(root->left) - 1);
        root->right = q.first;
        upd(root);
        return { root, q.second };
    }
    else {
        std::pair<Node*, Node*> q = split(root->left, sz);
        root->left = q.second;
        upd(root);
        return { q.first, root };
    }
}

Node* merge(Node* left, Node* right) {
    if (!left) {
        return right;
    }
    if (!right) {
        return left;
    }

    if (left->p > right->p) {
        left->right = merge(left->right, right);
        upd(left);
        return left;
    }
    else {
        right->left = merge(left, right->left);
        upd(right);
        return right;
    }
}

void print1(Node* node) {
    if (!node) return;
    print1(node->left);
    std::cout << node->key << std::endl;
    print1(node->right);
}

int find_zero_idx(Node* root) {
    if (!root) {
        return 0;
    }
    if (root->first_zero == nullptr || root->first_zero == root) {
        return root->idx;
    }
    if (root->first_zero) {
        return find_zero_idx(root->first_zero);

    }
    return 0;

}

void insert(Node*& root, int idx, int key) {
    if (root) {
        std::pair<Node*, Node*> q1 = split(root, idx);
        std::pair<Node*, Node*> q2 = split(q1.first, idx - 1);
        if (q2.second->key == 0) {
            if (q2.second->first_zero) {
                q2.second->first_zero->key = key;
                q2.second->first_zero = nullptr;
            }
            root = merge(q2.first, merge(q2.second, q1.second));
        }
        else {
            int zero_idx = find_zero_idx(q1.second) - idx;
            std::pair<Node*, Node*> q3 = split(q1.second, zero_idx);
            std::pair<Node*, Node*> q4 = split(q3.first, zero_idx - 1);
            root = merge(merge(merge(q2.first, new Node(key, idx)), q2.second), merge(q4.first, q3.second));
            if (zero_idx + idx >= last) {
                last += 1;
            }
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    Node* root = nullptr;

    int n = 0, m = 0;
    std::cin >> n >> m;

    last = 0;

    const int ssize = 300000;

    for (int i = 1; i <= ssize; i += 1) {
        root = merge(root, new Node(0, i));
    }
    for (int i = 1; i <= n; i += 1) {
        int l = 0;
        std::cin >> l;
        insert(root, l, i);
        last = std::max(last, l);
    }
    if (root) {
        std::cout << last << std::endl;
        if (last >= 1) {
            std::pair<Node*, Node*> q = split(root, last);
            print1(q.first);
        }
        else {
            print1(root);
        }
    }

    return 0;
}