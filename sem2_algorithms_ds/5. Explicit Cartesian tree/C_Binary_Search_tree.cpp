#include<iostream>
#include<random>
#include<string>

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

Node* my_delete(Node* tree, long long val) {
    if (!tree) {
        return nullptr;
    }
    else if (tree->value == val) {
        Node* tmp = merge(tree->left, tree->right);
        delete tree;
        return tmp;
    }
    else if (tree->value < val) {
        tree->right = my_delete(tree->right, val);
    }
    else if (tree->value > val) {
        tree->left = my_delete(tree->left, val);
    }
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

std::string prev(const Node* tree, const long long val, long long prev_) {

    if (!tree) {
        if (prev_ == val) {
            return "none";
        }
        else {
            return std::to_string(prev_);
        }
    }
    if (tree->value >= val) {
        if (!tree->left) {
            if (prev_ == val) {
                return "none";
            }
            return std::to_string(prev_);
        }
        else {
            return prev(tree->left, val, prev_);
        }
    }
    else if (tree->value < val) {
        prev_ = tree->value;
        if (!tree->right) {
            if (prev_ == val) {
                return "none";
            }
            return std::to_string(prev_);
        }
        else {
            return prev(tree->right, val, prev_);
        }
    }
    return std::to_string(prev_);
}

std::string next(const Node* tree, const long long val, long long next_) {
    if (!tree) {
        if (next_ == val) {
            return "none";
        }
        else {
            return std::to_string(next_);
        }
    }
    if (tree->value <= val) {
        if (!tree->right) {
            if (next_ == val) {
                return "none";
            }
            return std::to_string(next_);
        }
        else {
            return next(tree->right, val, next_);
        }
    }
    else if (tree->value > val) {
        next_ = tree->value;
        if (!tree->left) {
            if (next_ == val) {
                return "none";
            }
            return std::to_string(next_);
        }
        else {
            return next(tree->left, val, next_);
        }
    }
    return std::to_string(next_);
}

int main() {
    Node* root = nullptr;

    std::string query = "";
    long long a = 0;

    while (std::cin >> query >> a) {
        if (query == "insert") {
            if (!exists(root, a)) {
                insert(root, a);
            }
        }
        else if (query == "delete") {
            root = my_delete(root, a);
        }
        else if (query == "exists") {
            if (exists(root, a)) {
                std::cout << "true" << std::endl;
            }
            else {
                std::cout << "false" << std::endl;
            }
        }
        else if (query == "next") {
            std::cout << next(root, a, a) << std::endl;
        }
        else if (query == "prev") {
            std::cout << prev(root, a, a) << std::endl;
        }
    }

}