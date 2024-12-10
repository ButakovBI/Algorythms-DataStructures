#include<iostream>
#include<vector>
#include<algorithm>
#include<random>
#include<string>
#include <cassert>

std::mt19937 rd;

struct Node {
    long long key = 0;
    int p = rd(), size = 1;

    long long square = 0;
    long long sum = 0;


    Node* left = nullptr, * right = nullptr;
    Node(long long key) : key(key) {
        square = key * key;
        sum = square;
    }

};



int size_of(Node* node) {
    return node ? node->size : 0;
}

long long sum_of(Node* node) {
    return node ? node->sum : 0;
}

void upd(Node* root) {

    root->size = 1 + size_of(root->left) + size_of(root->right);
    root->sum = sum_of(root->left) + root->square + sum_of(root->right);
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

Node* ctrlx(Node*& root, int L, int R) {
    std::pair<Node*, Node*> q1 = split(root, R);
    std::pair<Node*, Node*> q2 = split(q1.first, L - 1);
    root = merge(q2.first, q1.second);
    return q2.second;
}

void print1(Node* node) {
    if (!node) return;

    print1(node->left);

    std::cout << node->key << ' ';
    print1(node->right);
}

void bankrupt(Node*& root, int v, int last) {
    if (v == 1) {
        std::pair<Node*, Node*> q1 = split(root, 2);

        std::pair<Node*, Node*> q2 = split(q1.first, 1);

        q2.second->sum -= q2.second->key * q2.second->key;
        q2.second->key += q2.first->key;
        q2.second->square = q2.second->key * q2.second->key;
        q2.second->sum += q2.second->square;

        root = merge(q2.second, q1.second);

    }
    else if (v == last) {
        std::pair<Node*, Node*> q1 = split(root, v - 2);

        std::pair<Node*, Node*> q2 = split(q1.second, 1);

        q2.first->sum -= q2.first->key * q2.first->key;
        q2.first->key += q2.second->key;
        q2.first->square = q2.first->key * q2.first->key;
        q2.first->sum += q2.first->square;

        root = merge(q1.first, q2.first);

    }
    else {
        std::pair<Node*, Node*> q1 = split(root, v + 1);
        std::pair<Node*, Node*> q2 = split(q1.first, v - 2);

        std::pair<Node*, Node*> q3 = split(q2.second, 1);
        std::pair<Node*, Node*> q4 = split(q3.second, 1);
        int new_size1 = (q4.first->key + 1) / 2;
        int new_size2 = q4.first->key / 2;

        q3.first->sum -= q3.first->key * q3.first->key;
        q3.first->key += new_size2;
        q3.first->square = q3.first->key * q3.first->key;
        q3.first->sum += q3.first->square;

        q4.second->sum -= q4.second->key * q4.second->key;
        q4.second->key += new_size1;
        q4.second->square = q4.second->key * q4.second->key;
        q4.second->sum += q4.second->square;

        root = merge(q2.first, merge(merge(q3.first, q4.second), q1.second));
    }
}

void bankrupt2(Node*& root) {
    std::pair<Node*, Node*> q = split(root, 1);

    q.first->sum -= q.first->key * q.first->key;
    q.first->key += q.second->key;
    q.first->square = q.first->key * q.first->key;
    q.first->sum += q.first->square;

    root = q.first;
}

void split_to_2(Node*& root, int idx) {
    Node* new1 = nullptr, * new2 = nullptr;

    std::pair<Node*, Node*> q1 = split(root, idx);
    std::pair<Node*, Node*> q2 = split(q1.first, idx - 1);

    int new_size1 = (q2.second->key + 1) / 2;
    int new_size2 = q2.second->key / 2;
    new1 = merge(new1, new Node(new_size2));
    new2 = merge(new2, new Node(new_size1));
    root = merge(merge(q2.first, merge(new1, new2)), q1.second);

}



int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n = 0, p = 0;
    std::cin >> n >> p;

    Node* root = nullptr;
    for (int i = 0; i < n; i += 1) {
        long long a = 0;
        std::cin >> a;
        root = merge(root, new Node(a));
    }
    std::cout << root->sum << std::endl;
    int k = 0;
    std::cin >> k;

    for (int i = 0; i < k; i += 1) {
        int e = 0, v = 0;
        std::cin >> e >> v;
        if (e == 1) {
            if (n > 2) {
                bankrupt(root, v, n);
                n -= 1;
                std::cout << root->sum << std::endl;
            }
            else if (n == 2) {
                bankrupt2(root);
                n -= 1;
                std::cout << root->sum << std::endl;
            }
        }
        else if (e == 2) {
            split_to_2(root, v);
            n += 1;
            std::cout << root->sum << std::endl;
        }
    }
    delete root;
}
