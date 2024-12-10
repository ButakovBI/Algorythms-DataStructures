#include<iostream>
#include<vector>

struct Node {
    Node* left_node = nullptr;
    Node* right_node = nullptr;
    size_t left_bound = 0;
    size_t right_bound = 0;

    static const int inf = 2147483647;

    int sum = 0;
    int minn = inf;
    std::pair<int, int> maxx = { -inf, 1 };
    int max_cnt = 1;
    int idx = 0;

    Node(const size_t left_bound, const size_t right_bound) :left_bound(left_bound), right_bound(right_bound) {
        if (left_bound + 1 < right_bound) {
            size_t mid = (left_bound + right_bound) / 2;
            left_node = new Node(left_bound, mid);
            right_node = new Node(mid, right_bound);
        }
    }

    void add(const size_t index, const int value) {

        this->sum += value;
        this->maxx = { std::max(maxx.first, value), idx };
        if (left_node) {
            if (index < left_node->right_bound) {
                left_node->add(index, value);
            }
            else {
                right_node->add(index, value);
            }
        }
    }

    int getSum(const int qleft, const int qright) const {
        if (qleft <= left_bound && right_bound <= qright) {
            return sum;
        }
        else if (qright <= left_bound || right_bound <= qleft) {
            return 0;
        }
        else {
            return left_node->getSum(qleft, qright) + right_node->getSum(qleft, qright);
        }
    }

    std::pair<int, int> getMax(const int qleft, const int qright) {
        if (qleft <= left_bound && right_bound <= qright) {
            return maxx;
        }
        else if (qright <= left_bound || right_bound <= qleft) {
            return { -inf, 1 };
        }
        else {
            std::pair<int, int> l = left_node->getMax(qleft, qright);
            std::pair<int, int> r = right_node->getMax(qleft, qright);
            if (l.first >= r.first) {
                return l;
            }
            else if (l.first < r.first) {
                return r;
            }
        }
    }

    int operator[] (const size_t index) const {
        return this->getSum(index, index + 1);
    }

    int operator[] (const std::pair <const size_t, const size_t>& p) const {
        return this->getSum(p.first, p.second);
    }

    void add1(const size_t index, const int value) {
        this->sum += value;
        this->maxx.first = value;
        if (left_node) {
            if (index < left_node->right_bound) {
                left_node->add1(index, value);
            }
            else {
                right_node->add1(index, value);
            }
        }
        this->maxx.first = std::max(getMax(this->left_bound, (this->left_bound + this->right_bound) / 2).first, getMax((this->left_bound + this->right_bound) / 2, this->right_bound).first);
    }

};

int main() {

    int n = 0, k = 0;
    std::cin >> n;
    std::vector<int> vec(n);

    for (int i = 0; i < n; i += 1) {
        int a = 0;
        std::cin >> a;
        vec[i] = a;
    }

    Node* segtree = new Node(0, vec.size());
    for (size_t i = 0; i < vec.size(); ++i) {
        segtree->add(i, vec[i]);
    }

    std::cin >> k;

    std::vector<int> vvv;

    for (int i = 0; i < k; i += 1) {
        char sym = 0;
        std::cin >> sym;
        if (sym == 's') {
            int left = 0, right = 0;
            std::cin >> left >> right;
            vvv.push_back(segtree->getMax(left - 1, right).first);
        }
        else if (sym == 'u') {

            int i = 0, val = 0;
            std::cin >> i >> val;
            segtree->add1(i - 1, val);
        }
    }

    for (auto& elem : vvv) {
        std::cout << elem << ' ';
    }
    return 0;
}