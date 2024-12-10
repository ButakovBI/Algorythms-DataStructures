#include<iostream>
#include<vector>
#include<algorithm>
#include<random>
#include <string>

std::mt19937 rd;

struct Node {
    int key = 0, p = rd(), size = 1;
    long long sum = 0;

    Node* left = nullptr, * right = nullptr;
    Node(int key) : key(key), sum(key) {
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
    std::cout << node->key << ' ';
    print(node->right);
}

Node* ctrlx(Node*& root, int L, int R) {
    std::pair<Node*, Node*> q1 = split(root, R);
    std::pair<Node*, Node*> q2 = split(q1.first, L - 1);
    root = merge(q2.first, q1.second);
    return q2.second;
}

void firstSwapQuery(Node*& root_even, Node*& root_noteven, int x, int y, int n) {
    int L_noteven = 0, R_noteven = 0, L_even = 0, R_even = 0;
    if (n % 2) {
        L_noteven = x / 2;
        R_noteven = (y + 1) / 2;
        L_even = (x - 1) / 2;
        R_even = y / 2;
    }
    else {
        L_noteven = x / 2;
        R_noteven = (y + 1) / 2;
        L_even = (x - 1) / 2;
        R_even = y / 2;
    }
    std::pair<Node*, Node*> q1 = split(root_even, R_even);
    std::pair<Node*, Node*> q2 = split(q1.first, L_even);

    std::pair<Node*, Node*> q3 = split(root_noteven, R_noteven);
    std::pair<Node*, Node*> q4 = split(q3.first, L_noteven);

    root_even = merge(q2.first, merge(q4.second, q1.second));

    root_noteven = merge(q4.first, merge(q2.second, q3.second));
}

long long secondSumQuery(Node* root_even, Node* root_noteven, int a, int b, int n) {
    int L_noteven = 0, R_noteven = 0, L_even = 0, R_even = 0;
    if (n % 2) {
        L_noteven = a / 2;
        R_noteven = (b + 1) / 2;
        L_even = (a - 1) / 2;
        R_even = b / 2;
    }
    else {
        L_noteven = a / 2;
        R_noteven = (b + 1) / 2;
        L_even = (a - 1) / 2;
        R_even = b / 2;
    }
    std::pair<Node*, Node*> q1 = split(root_even, R_even);
    std::pair<Node*, Node*> q2 = split(q1.first, L_even);

    std::pair<Node*, Node*> q3 = split(root_noteven, R_noteven);
    std::pair<Node*, Node*> q4 = split(q3.first, L_noteven);

    long long ans = getSum(q2.second) + getSum(q4.second);
    root_even = merge(q2.first, merge(q2.second, q1.second));
    root_noteven = merge(q4.first, merge(q4.second, q3.second));
    return ans;

}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int cnt = 0;
    int n = 0, m = 0;
    while (std::cin >> n >> m && (n != 0 && m != 0)) {
        ++cnt;
        Node* root_even = nullptr;
        Node* root_noteven = nullptr;
        std::cout << "Swapper " << cnt << ":" << "\n";
        for (int i = 1; i <= n; ++i) {
            int num = 0;
            std::cin >> num;
            if (i % 2) {
                root_noteven = merge(root_noteven, new Node(num));
            }
            else {
                root_even = merge(root_even, new Node(num));
            }
        }
        for (int i = 0; i < m; ++i) {
            short cmd = 0;
            std::cin >> cmd;
            if (cmd == 1) {
                int x = 0, y = 0;
                std::cin >> x >> y;
                firstSwapQuery(root_even, root_noteven, x, y, n);
            }
            if (cmd == 2) {
                int a = 0, b = 0;
                std::cin >> a >> b;
                std::cout << secondSumQuery(root_even, root_noteven, a, b, n) << "\n";
            }
        }
        delete root_even;
        delete root_noteven;
        std::cout << std::endl;
    }

}