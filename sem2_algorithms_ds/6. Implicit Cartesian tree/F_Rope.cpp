#include<iostream>
#include<vector>
#include<algorithm>
#include<random>
#include <string>

std::mt19937 rd;

struct Node {
    char key = 0;
    int p = rd(), size = 1;
    long long sum = 0;

    Node* left = nullptr, * right = nullptr;
    Node(char key) : key(key), sum(key) {
    }
    ~Node() = default;
};

int size_of(Node* node) {
    return node ? node->size : 0;
}

void upd(Node* root) {
    root->size = 1 + size_of(root->left) + size_of(root->right);
}

long long getSum(Node* root) {
    if (root) {
        return root->sum;
    }
    return 0;
}

void upd_sum(Node* root) {
    if (root) {
        root->sum = root->key + getSum(root->left) + getSum(root->right);
    }
}

std::pair<Node*, Node*> split(Node* root, int sz) {
    if (!root) return { nullptr, nullptr };
    if (size_of(root->left) < sz) {
        std::pair<Node*, Node*> q = split(root->right, sz - size_of(root->left) - 1);
        root->right = q.first;
        upd(root);
        upd_sum(root);
        return { root, q.second };
    }
    else {
        std::pair<Node*, Node*> q = split(root->left, sz);
        root->left = q.second;
        upd(root);
        upd_sum(root);
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
        upd_sum(left);
        return left;
    }
    else {
        right->left = merge(left, right->left);
        upd(right);
        upd_sum(right);
        return right;
    }
}

void print(Node* node) {
    if (!node) return;
    print(node->left);
    std::cout << node->key;
    print(node->right);
}

Node* ctrlx(Node*& root, int L, int R) {
    std::pair<Node*, Node*> q1 = split(root, R + 1);
    std::pair<Node*, Node*> q2 = split(q1.first, L);
    root = merge(q2.first, q1.second);
    return q2.second;
}

void rebuildStr(Node* root, size_t idx1, size_t idx2, size_t idx_to) {
    Node* wow = ctrlx(root, idx1, idx2);
    std::pair<Node*, Node*> q = split(root, idx_to);
    root = merge(q.first, merge(wow, q.second));
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    Node* root = nullptr;

    std::string str = "";
    std::cin >> str;
    for (auto& sym : str) {
        root = merge(root, new Node(sym));
    }
    int n = 0;
    std::cin >> n;
    for (size_t i = 0; i < n; i += 1) {
        size_t idx1 = 0, idx2 = 0, idx_to = 0;
        std::cin >> idx1 >> idx2 >> idx_to;
        rebuildStr(root, idx1, idx2, idx_to);
    }
    print(root);
}