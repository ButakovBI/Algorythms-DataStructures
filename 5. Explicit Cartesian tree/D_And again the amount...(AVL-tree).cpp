#include <iostream>

struct Node { //avl

    long long value = 0;
    long long height = 1;

    long long sum = 0;

    long long min = 1000000000;
    long long max = -1000000000;

    Node* left = nullptr, * right = nullptr;
    Node(long long val) : value(val), min(val), max(val), sum(0), height(1) {
    }
    ~Node() {
        delete left;
        delete right;
    }
};


void calcSum(Node*& tree) {
    long long left_sum = 0, right_sum = 0;
    if (tree->left) {
        left_sum = tree->left->sum;
    }
    if (tree->right) {
        right_sum = tree->right->sum;
    }
    tree->sum = left_sum + right_sum;
    if (tree->left) {
        tree->sum += tree->left->value;
    }
    if (tree->right) {
        tree->sum += tree->right->value;
    }
}

void calcHeight(Node*& tree) {
    long long left_height = 0, right_height = 0;
    if (tree->left) {
        left_height = tree->left->height;
    }
    if (tree->right) {
        right_height = tree->right->height;
    }
    tree->height = std::max(left_height, right_height) + 1;
}

void calcMinMax(Node*& tree) {
    long long left_min = 1000000000, right_min = 1000000000, left_max = -1000000000, right_max = -1000000000;
    if (tree->left) {
        left_min = tree->left->min;
        left_max = tree->left->max;
    }
    if (tree->right) {
        right_min = tree->right->min;
        right_max = tree->right->max;
    }
    tree->min = std::min(std::min(left_min, right_min), tree->value);
    tree->max = std::max(std::max(left_max, right_max), tree->value);
}

long long getDiffHeight(Node*& tree) {
    long long right_height = 0, left_height = 0;
    if (tree->right) {
        right_height = tree->right->height;
    }
    if (tree->left) {
        left_height = tree->left->height;
    }
    return right_height - left_height;
}

Node* rightRotation(Node* tree) {
    Node* tmp_left = tree->left;
    tree->left = tmp_left->right;
    tmp_left->right = tree;

    calcHeight(tree);
    calcSum(tree);
    calcMinMax(tree);
    calcHeight(tmp_left);
    calcSum(tmp_left);
    calcMinMax(tmp_left);

    return tmp_left;
}

Node* leftRotation(Node* tree) {
    Node* tmp_right = tree->right;
    tree->right = tmp_right->left;
    tmp_right->left = tree;

    calcHeight(tree);
    calcSum(tree);
    calcMinMax(tree);
    calcHeight(tmp_right);
    calcSum(tmp_right);
    calcMinMax(tmp_right);

    return tmp_right;
}

Node* balance(Node* tree) {
    if (getDiffHeight(tree) >= 2) {
        if (getDiffHeight(tree->right) < 0) {
            tree->right = rightRotation(tree->right);
        }
        return leftRotation(tree);
    }
    if (getDiffHeight(tree) <= -2) {
        if (getDiffHeight(tree->left) > 0) {
            tree->left = leftRotation(tree->left);
        }
        return rightRotation(tree);
    }
    return tree;
}

Node* insert(Node* tree, long long value) {
    if (!tree) {
        return new Node(value);
    }
    if (value < tree->value) {
        tree->left = insert(tree->left, value);
    }
    else {
        tree->right = insert(tree->right, value);
    }
    calcHeight(tree);
    calcSum(tree);
    calcMinMax(tree);
    return balance(tree);
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
    return false;
}

long long getSum(Node*& tree, long long left, long long right) {
    if (!tree) {
        return 0;
    }
    else if (tree->value > right) {
        return getSum(tree->left, left, right);
    }
    else if (tree->value < left) {
        return getSum(tree->right, left, right);
    }
    else if ((!tree->left) && (!tree->right)) {
        return tree->value;
    }
    else if ((left <= tree->min) && (tree->max <= right)) {
        return tree->sum + tree->value;
    }
    return getSum(tree->left, left, right) + getSum(tree->right, left, right) + tree->value;

}

void print(const Node* tree) {
    if (!tree) {
        return;
    }
    print(tree->left);
    std::cout << tree->value << " ";
    print(tree->right);
}



int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    Node* root = nullptr;

    long long n = 0;
    std::cin >> n;
    char prev = 0;
    long long sum_ = 0;
    const long long nnn = 1000000000;

    for (size_t i = 0; i < n; ++i) {
        char sym = 0;
        std::cin >> sym;
        if (sym == '+') {
            long long a = 0;
            std::cin >> a;

            if (prev == '?') {
                long long num = (a + sum_) % nnn;
                if (!exists(root, num)) {
                    root = insert(root, num);
                }
            }
            else {
                if (!exists(root, a)) {
                    root = insert(root, a);
                }
            }
        }
        else if (sym == '?') {
            long long a = 0, b = 0;
            std::cin >> a >> b;
            sum_ = getSum(root, a, b);
            std::cout << sum_ << std::endl;
        }
        prev = sym;
    }
}
