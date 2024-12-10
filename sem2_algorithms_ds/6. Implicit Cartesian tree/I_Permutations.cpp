#include<iostream>
#include<vector>
#include<algorithm>
#include<random>
#include<string>

std::mt19937 rd;

const int inf = 1e9 + 7;
const int fact_size = 1000000;

std::vector<char> syms = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j' };

std::vector<int>fact(fact_size), revfact(fact_size);

int mul(long long a, long long b) {
    return (a * b) % inf;
}

int sum(int a, int b) {
    if (a + b >= inf) {
        return a + b - inf;
    }
    return a + b;
}

int sub(int a, int b) {
    if (a - b < 0) {
        return a - b + inf;
    }
    return a - b;
}

int bin(int x, int p) {
    if (p == 0) {
        return 1;
    }
    if (p % 2) {
        return mul(bin(x, p - 1), x);
    }

    return bin(mul(x, x), p / 2);
}

struct Node {
    char key = 0;
    long long idx_key = 0;
    int p = rd(), size = 1;
    int plus = 0;
    bool rev_flag = false;
    std::vector<long long> cnt_vec = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    Node* left = nullptr, * right = nullptr;
    Node(char key) : key(key), idx_key(key - 97) {
        ++cnt_vec[idx_key];
    }

};


int size_of(Node* node) {
    return node ? node->size : 0;
}

void move(Node* root) {

    int D = root->plus % 10;
    reverse(root->cnt_vec.begin(), root->cnt_vec.end());
    reverse(root->cnt_vec.begin(), root->cnt_vec.begin() + D);
    reverse(root->cnt_vec.begin() + D, root->cnt_vec.end());
    root->idx_key = (root->idx_key + D) % 10;
    root->key = syms[root->idx_key];
}

void push(Node* root) {

    if (root && (root->plus || root->rev_flag)) {

        if (root->rev_flag) {
            std::swap(root->left, root->right);
            if (root->left) {
                root->left->rev_flag ^= true;
            }
            if (root->right) {
                root->right->rev_flag ^= true;
            }
        }
        if (root->plus) {
            move(root);
            if (root->left) {
                root->left->plus += root->plus % 10;
            }
            if (root->right) {
                root->right->plus += root->plus % 10;
            }
        }
        root->plus = 0;
        root->rev_flag = 0;
    }
}

void rev(Node* root) {
    if (root && root->rev_flag) {
        std::swap(root->left, root->right);
        if (root->left) {
            root->left->rev_flag ^= true;
        }
        if (root->right) {
            root->right->rev_flag ^= true;
        }
        root->rev_flag = false;
    }
}

void updCntRepeat(Node* root) {
    push(root);
    if (!root) {
        return;
    }

    for (int i = 0; i < 10; ++i) {
        if (i == root->idx_key) {
            root->cnt_vec[i] = 1;
        }
        else {
            root->cnt_vec[i] = 0;
        }
    }

    if (root->right) {
        push(root->right);
        for (int i = 0; i < 10; ++i) {
            root->cnt_vec[i] += root->right->cnt_vec[i];
        }
    }
    if (root->left) {
        push(root->left);
        for (int i = 0; i < 10; ++i) {
            root->cnt_vec[i] += root->left->cnt_vec[i];
        }
    }
    root->size = 1 + size_of(root->left) + size_of(root->right);
}

std::pair<Node*, Node*> split(Node* root, int sz) {
    if (!root) return { nullptr, nullptr };
    rev(root);
    push(root);

    if (size_of(root->left) < sz) {
        std::pair<Node*, Node*> q = split(root->right, sz - size_of(root->left) - 1);
        root->right = q.first;
        updCntRepeat(root);
        return { root, q.second };
    }
    else {
        std::pair<Node*, Node*> q = split(root->left, sz);
        root->left = q.second;
        updCntRepeat(root);
        return { q.first, root };
    }
}

Node* merge(Node* left, Node* right) {
    rev(left);
    push(left);
    rev(right);
    push(right);

    if (!left) {
        return right;
    }
    if (!right) {
        return left;
    }

    if (left->p > right->p) {
        left->right = merge(left->right, right);
        updCntRepeat(left);
        return left;
    }
    else {
        right->left = merge(left, right->left);
        updCntRepeat(right);
        return right;
    }
}

void print(Node* node) {
    push(node);
    rev(node);
    if (!node) return;
    print(node->left);
    print(node->right);
}

void flip(Node* root, int L, int R) {
    std::pair<Node*, Node*> q1 = split(root, R);
    std::pair<Node*, Node*> q2 = split(q1.first, L - 1);

    q2.second->rev_flag ^= true;

    root = merge(q2.first, merge(q2.second, q1.second));
}

void change(Node* root, int L, int R, int D) {
    std::pair<Node*, Node*> q1 = split(root, R);
    std::pair<Node*, Node*> q2 = split(q1.first, L - 1);

    q2.second->plus += D % 10;

    root = merge(q2.first, merge(q2.second, q1.second));

}



int getPerm(Node* root, int L, int R) {

    std::pair<Node*, Node*> q1 = split(root, R);
    std::pair<Node*, Node*> q2 = split(q1.first, L - 1);

    int cnt_all = R - L + 1;

    int ans = 1;

    int first = revfact[q2.second->cnt_vec[0]];
    if (first != 0 && first != 1) {
        ans = mul(fact[cnt_all], first);
    }
    else {
        ans = mul(fact[cnt_all], 1);
    }

    for (int i = 1; i < 10; ++i) {
        if (q2.second->cnt_vec[i] == 0 || q2.second->cnt_vec[i] == 1) {
            continue;
        }
        ans = mul(ans, revfact[q2.second->cnt_vec[i]]);
    }
    root = merge(q2.first, merge(q2.second, q1.second));
    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    fact[0] = 1;
    for (int i = 1; i < fact.size(); ++i) {
        fact[i] = mul(fact[i - 1], i);
    }

    revfact[revfact.size() - 1] = bin(fact[fact.size() - 1], inf - 2);

    for (int i = revfact.size() - 2; i > 0; --i) {
        revfact[i] = mul(revfact[i + 1], i + 1);
    }

    Node* root = nullptr;
    int n = 0, m = 0;
    std::cin >> n;
    std::string str = "";
    std::cin >> str;
    for (char& sym : str) {
        root = merge(root, new Node(sym));
    }
    std::cin >> m;
    for (int i = 0; i < m; ++i) {
        int sym = 0;
        std::cin >> sym;

        if (sym == -1) {
            int L = 0, R = 0;
            std::cin >> L >> R;
            flip(root, L, R);

        }
        else if (sym == 0) {
            int L = 0, R = 0, D = 0;
            std::cin >> L >> R >> D;
            change(root, L, R, D);
        }
        else if (sym == 1) {
            int L = 0, R = 0;
            std::cin >> L >> R;
            std::cout << getPerm(root, L, R) << "\n";
        }

    }
    return 0;
}