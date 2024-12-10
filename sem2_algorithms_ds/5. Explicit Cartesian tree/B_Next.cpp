#include<iostream>
#include<random>

std::mt19937_64 rd;

struct Node
{
    long long value = 0;
    long long pr = rd();

    Node* left = nullptr, * right = nullptr;
    Node(long long value) : value(value) {
    }
    ~Node() = default;
};

std::pair<Node*, Node*> split(Node* tree, long long key) {
    if (!tree) return { nullptr, nullptr };
    if (key < tree->value) {
        auto query = split(tree->left, key);
        tree->left = query.second;
        return { query.first, tree };
    }
    else {
        auto query = split(tree->right, key);
        tree->right = query.first;
        return { tree, query.second };
    }
}

Node* merge(Node* left_tree, Node* right_tree) {
    if (!left_tree) return right_tree;
    if (!right_tree) return left_tree;
    if (left_tree->pr < right_tree->pr) {
        right_tree->left = merge(left_tree, right_tree->left);
        return right_tree;
    }
    else {
        left_tree->right = merge(left_tree->right, right_tree);
        return left_tree;
    }
}

void insert(Node*& tree, const long long value) {
    Node* tmp = new Node(value);
    auto query = split(tree, value);
    tree = merge(merge(query.first, tmp), query.second);
}

void print(const Node* tree) {
    if (!tree) return;
    print(tree->left);
    std::cout << tree->value << " ";
    print(tree->right);
}

Node* delete_(Node* tree, long long val) {
    if (!tree) {
        return nullptr;
    }
    else if (tree->value == val) {
        Node* tmp = merge(tree->left, tree->right);
        delete tree;
        return tmp;
    }
    else if (tree->value < val) {
        tree->right = delete_(tree->right, val);
    }
    else if (tree->value > val) {
        tree->left = delete_(tree->left, val);
    }
    return tree;
}

void exists(const Node* tree, long long val) {
    if (!tree) {
        std::cout << "false" << std::endl;
        return;
    }
    if (val == tree->value) {
        std::cout << "true" << std::endl;
        return;
    }
    else if (val < tree->value) {
        return exists(tree->left, val);
    }
    else if (val > tree->value) {
        return exists(tree->right, val);
    }
}

void prev(const Node* tree, const long long val, long long prev_) {
    if (!tree) {
        if (prev_ == val) {
            std::cout << "none" << std::endl;
            return;
        }
        else {
            std::cout << prev_ << std::endl;
        }
    }
    if (tree->value >= val) {
        if (!tree->left) {
            if (prev_ == val) {
                std::cout << "none" << std::endl;
                return;
            }
            std::cout << prev_ << std::endl;
            return;
        }
        else {
            prev(tree->left, val, prev_);
        }
    }
    else if (tree->value < val) {
        prev_ = tree->value;
        if (!tree->right) {
            if (prev_ == val) {
                std::cout << "none" << std::endl;
                return;
            }
            std::cout << prev_ << std::endl;
            return;
        }
        else {
            prev(tree->right, val, prev_);
        }
    }
}

long long next(const Node* tree, const long long val, long long next_) {
    if (!tree) {
        return next_;
    }
    if (tree->value == val) {
        return val;
    }
    if (tree->value < val) {
        if (!tree->right) {
            if (next_ == val) {
                return next_;
            }
            return next_;
        }
        else {
            return next(tree->right, val, next_);
        }
    }
    else if (tree->value > val) {
        next_ = tree->value;
        if (!tree->left) {
            if (next_ == val) {
                return next_;
            }
            return next_;
        }
        else {
            return next(tree->left, val, next_);
        }
    }
    return next_;
}


int main() {

    Node* root = nullptr;

    long long n = 0;
    std::cin >> n;
    long long prev_ = 0;
    bool flag = false;
    const long long nnn = 1000000000;

    for (size_t i = 0; i < n; ++i) {
        char sym = 0;
        long long a = 0;
        std::cin >> sym >> a;
        if (sym == '?') {
            prev_ = next(root, a, -1);
            std::cout << prev_ << std::endl;
            if (prev_ != -1) {
                flag = true;
            }
        }
        else if (sym == '+') {
            if (flag) {
                long long num = (prev_ + a) % nnn;
                insert(root, num);
                flag = false;
            }
            else {
                insert(root, a);
            }
        }
    }

}