#include<iostream>
#include<vector>
#include<algorithm>
#include<random>
#include <string>

std::mt19937 rd;

struct Node {
    int key, p = rd(), size = 1;
    Node* left = nullptr, * right = nullptr;
    Node(int key) : key(key) {}

};

int size_of(Node* node) {
    return node ? node->size : 0;
}

void upd(Node* root) {
    root->size = 1 + size_of(root->left) + size_of(root->right);
}

int upd_min(Node* node) {
    if (!node) {
        return 10000000;
    }
    return std::min(node->key, std::min(upd_min(node->left), upd_min(node->right)));
}

void myReverse(Node* root) {
    if (!root) {
        return;
    }
    std::swap(root->left, root->right);
    myReverse(root->left);
    myReverse(root->right);
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

void print(Node* node) {
    if (!node) return;
    print(node->left);
    std::cout << node->key << ' ';
    print(node->right);
}

Node* ctrlx(Node*& root, int L, int R) {
    std::pair<Node*, Node*> q1 = split(root, R);
    std::pair<Node*, Node*> q2 = split(q1.first, L - 1);
    root = merge(q2.first, q1.second);
    return q2.second;
}

void flip(Node* root, int L, int R) {
    std::pair<Node*, Node*> q1 = split(root, R);
    std::pair<Node*, Node*> q2 = split(q1.first, L - 1);

    myReverse(q2.second);
    root = merge(q2.first, merge(q2.second, q1.second));
}

void findMin(Node* root, int L, int R) {
    std::pair<Node*, Node*> q1 = split(root, R);
    std::pair<Node*, Node*> q2 = split(q1.first, L);

    std::cout << upd_min(q2.second) << "\n";

    merge(q2.first, merge(q2.second, q1.second));

}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    Node* root = nullptr;
    int n = 0, m = 0;
    std::cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        int a = 0;
        std::cin >> a;
        root = merge(root, new Node(a));
    }

    for (int i = 0; i < m; ++i) {
        std::string query = "";
        std::cin >> query;
        if (query == "del") {
            int del_idx = 0;
            std::cin >> del_idx;
            root = merge(ctrlx(root, 0, del_idx - 1), ctrlx(root, del_idx + 1, root->size));
        }
        else if (query == "add") {
            int add_idx = 0, add_num = 0;
            std::cin >> add_idx >> add_num;
            if (!root) {

                root = new Node(add_num);
            }
            else {
                root->size += 1;
                root = merge(merge(ctrlx(root, 0, add_idx), new Node(add_num)), ctrlx(root, add_idx + 1, root->size));
            }
        }
    }
    if (root) {
        std::cout << root->size << "\n";
    }
    else {
        std::cout << 0 << "\n";
    }
    print(root);
    return 0;
}