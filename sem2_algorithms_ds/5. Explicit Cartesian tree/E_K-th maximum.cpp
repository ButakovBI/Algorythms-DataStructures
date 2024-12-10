#include<iostream>
#include<random>
#include <string>

std::mt19937_64 rd;

struct Node
{
    long long value = 0;
    long long pr = rd();

    long long size = 0;

    Node* left = nullptr, * right = nullptr;
    Node(long long value) : value(value) {
    }
    ~Node() = default;
};

long long size_of(Node* node) {
    return node ? node->size : 0;
}

void upd(Node* root) {
    if (root) {
        root->size = 1 + size_of(root->left) + size_of(root->right);
    }
}

std::pair<Node*, Node*> split(Node* tree, long long key) {
    if (!tree) {
        return { nullptr, nullptr };
    }
    if (key < tree->value) {
        auto query = split(tree->left, key);
        tree->left = query.second;
        upd(tree);
        upd(tree->left);
        upd(tree->right);
        return { query.first, tree };
    }
    else {
        auto query = split(tree->right, key);
        tree->right = query.first;
        upd(tree);
        upd(tree->left);
        upd(tree->right);
        return { tree, query.second };
    }
}

Node* merge(Node* tree, Node* left_tree, Node* right_tree) {
    if (!left_tree) {
        return right_tree;
    }
    if (!right_tree) {
        return left_tree;
    }
    if (left_tree->pr < right_tree->pr) {
        right_tree->left = merge(tree, left_tree, right_tree->left);
        upd(right_tree);
        return right_tree;
    }
    else {
        left_tree->right = merge(tree, left_tree->right, right_tree);
        upd(left_tree);
        return left_tree;
    }

}

void insert(Node*& tree, const long long value) {
    Node* tmp = new Node(value);
    upd(tmp);
    auto query = split(tree, value);
    upd(tree);
    tree = merge(tree, merge(tree, query.first, tmp), query.second);
    upd(tree);
    upd(tree->left);
    upd(tree->right);
}

void print(const Node* tree) {
    if (!tree) return;
    print(tree->left);
    std::cout << tree->value << " ";
    print(tree->right);
}

Node* my_delete(Node* tree, long long val) {
    if (!tree) {
        return nullptr;
    }
    else if (tree->value == val) {
        Node* tmp = merge(tree, tree->left, tree->right);
        delete tree;
        upd(tmp);
        return tmp;
    }
    else if (tree->value < val) {
        tree->right = my_delete(tree->right, val);
    }
    else if (tree->value > val) {
        tree->left = my_delete(tree->left, val);
    }
    upd(tree);
    upd(tree->left);
    upd(tree->right);
    return tree;
}

bool exists(const Node* tree, long long val) {
    if (!tree) {
        return false;
    }
    if (val == tree->value) {
        return true;
    }
    else if (val < tree->value) {
        return exists(tree->left, val);
    }
    else if (val > tree->value) {
        return exists(tree->right, val);
    }
}

long long findkMax(const Node* tree, long long key) {
    long long left_size = 0;
    if (!tree) {
        return 0;
    }
    if (tree->left) {
        left_size = tree->left->size;
    }
    if (left_size == key) {
        return tree->value;
    }
    else if (left_size > key) {
        return findkMax(tree->left, key);
    }
    else {
        key -= left_size + 1;
        return findkMax(tree->right, key);
    }
}

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    Node* root = nullptr;
    int32_t n = 0;
    std::cin >> n;

    long long ssize = 0;

    for (size_t i = 0; i < n; i += 1) {
        short c = 0;
        long long k = 0;
        std::cin >> c >> k;

        if (c == 1) {
            insert(root, k);
            ++ssize;
        }
        if (c == 0) {
            std::cout << findkMax(root, ssize - k) << std::endl;
        }
        if (c == -1) {
            root = my_delete(root, k);
            --ssize;
        }
    }
}