#include <iostream>
#include <vector>
#include <algorithm>

struct Node
{
    int32_t val = 0;
    int32_t pr = 0;
    uint32_t idx = 0;

    Node* parent = nullptr, * left_son = nullptr, * right_son = nullptr;
    Node(int32_t val, int32_t pr, size_t idx) : val(val), pr(pr), idx(idx) {
    }
    ~Node() {
        delete parent;
        delete left_son;
        delete right_son;
    }
};

bool cmp(Node* left, Node* right) {
    return left->val < right->val;
}

void build(Node*& tree, size_t n, std::vector<int32_t>& prs, std::vector<Node*>& sortVec) {
    tree = sortVec[0];
    Node* last = tree;
    for (size_t i = 1; i < n; i += 1) {
        if (last->pr < prs[i]) {
            last->right_son = sortVec[i];
            last->right_son->parent = last;
            last = last->right_son;
        }
        else {
            Node* now = last;
            while (now->parent && (now->pr > sortVec[i]->pr)) {
                now = now->parent;
            }
            if (now->pr > sortVec[i]->pr) {
                last = sortVec[i];
                last->left_son = now;
                now->parent = last;
            }
            else {
                last = sortVec[i];
                last->left_son = now->right_son;
                now->right_son->parent = last;
                last->parent = now;
                now->right_son = last;
            }
        }
    }
    while (last->parent) {
        last = last->parent;
    }
    tree = last;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    Node* root = nullptr;

    size_t n = 0;
    std::cin >> n;

    std::vector<int32_t> values(n);
    std::vector<int32_t> prs(n);
    std::vector<size_t> idxs(n);

    std::vector<Node*> sortVec(n);
    std::vector<Node*> originalVec(n);

    for (size_t i = 0; i < n; i += 1) {
        int32_t a = 0;
        int32_t b = 0;
        std::cin >> a >> b;
        Node* elem = new Node(a, b, i + 1);
        sortVec[i] = elem;
        originalVec[i] = elem;
    }

    std::sort(sortVec.begin(), sortVec.end(), cmp);
    for (size_t i = 0; i < n; i += 1) {
        values[i] = sortVec[i]->val;
        prs[i] = sortVec[i]->pr;
        idxs[i] = sortVec[i]->pr;
    }

    build(root, n, prs, sortVec);

    std::cout << "YES" << "\n";
    for (size_t i = 0; i < n; i += 1) {
        Node* now = originalVec[i];
        std::cout << ((now->parent) ? now->parent->idx : 0) << ' ';
        std::cout << ((now->left_son) ? now->left_son->idx : 0) << ' ';
        std::cout << ((now->right_son) ? now->right_son->idx : 0) << "\n";
    }
}