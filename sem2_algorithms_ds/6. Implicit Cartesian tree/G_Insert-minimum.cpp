#include<iostream>
#include<vector>
#include<algorithm>
#include<random>
#include <string>

std::mt19937 rd;

const int sup = 1000000000;

struct Node {
    int key = 0, p = rd(), size = 1;
    int min = sup;
    bool rev_flag = false;

    Node* left = nullptr, * right = nullptr;
    Node(int key) : key(key) {
        min = std::min(min, key);
    }
};

int size_of(Node* node) {
    return node ? node->size : 0;
}

void upd(Node* root) {
    root->size = 1 + size_of(root->left) + size_of(root->right);
}

void upd_min(Node* root) {
    int left_min = sup, right_min = sup;
    if (root->left) {
        left_min = root->left->min;
    }
    if (root->right) {
        right_min = root->right->min;
    }
    root->min = std::min(root->key, std::min(left_min, right_min));
}

void myReverse(Node* root) {
    if (root && root->rev_flag) {
        return;
    }
    std::swap(root->left, root->right);
    if (root->left) {
        root->left->rev_flag ^= true;
    }
    if (root->right) {
        root->right->rev_flag ^= true;
    }

    root->rev_flag = false;
}

std::pair<Node*, Node*> split(Node* root, int sz) {
    if (!root) return { nullptr, nullptr };
    if (size_of(root->left) < sz) {
        std::pair<Node*, Node*> q = split(root->right, sz - size_of(root->left) - 1);
        root->right = q.first;
        upd(root);
        upd_min(root);
        return { root, q.second };
    }
    else {
        std::pair<Node*, Node*> q = split(root->left, sz);
        root->left = q.second;
        upd(root);
        upd_min(root);
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
        upd_min(left);
        return left;
    }
    else {
        right->left = merge(left, right->left);
        upd(right);
        upd_min(right);
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
    std::pair<Node*, Node*> q1 = split(root, R - 1);
    std::pair<Node*, Node*> q2 = split(q1.first, L - 1);

    std::cout << q2.second->min << "\n";

    root = merge(q2.first, merge(q2.second, q1.second));

}

void findMin(Node* root, int L, int R) {
    std::pair<Node*, Node*> q1 = split(root, R);
    std::pair<Node*, Node*> q2 = split(q1.first, L - 1);

    std::cout << q2.second->min << "\n";

    merge(q2.first, merge(q2.second, q1.second));

}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    Node* root = nullptr;
    int n = 0;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        char sym = 0;
        std::cin >> sym;
        if (sym == '?') {
            int idx1 = 0, idx2 = 0;
            std::cin >> idx1 >> idx2;
            findMin(root, idx1, idx2);
        }
        else if (sym == '+') {
            int idx = 0, val = 0;
            std::cin >> idx >> val;
            if (!root) {
                root = new Node(val);
            }
            else {
                root->size += 1;
                root = merge(merge(ctrlx(root, 0, idx), new Node(val)), ctrlx(root, idx + 1, root->size));
            }
        }
    }
    return 0;
}