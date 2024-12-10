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

        if (value > maxx.first) {
            idx = index + 1;
            this->max_cnt = 1;
        }
        else if (value == maxx.first) {
            this->max_cnt += 1;
        }
        this->sum += value;
        this->minn = std::min(minn, value);
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

    int getMin(const int qleft, const int qright) {
        if (qleft <= left_bound && right_bound <= qright) {
            return minn;
        }
        else if (qright <= left_bound || right_bound <= qleft) {
            return inf;
        }
        else {
            return std::min(left_node->getMin(qleft, qright), right_node->getMin(qleft, qright));
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

};

int main() {
    int n = 0;
    std::cin >> n;

    std::vector<int> v(n);
    for (int i = 0; i < n; i += 1) {
        int a = 0;
        std::cin >> a;
        v[i] = a;
    }

    Node* segtree = new Node(0, v.size());
    for (size_t i = 0; i < v.size(); ++i) {
        segtree->add(i, v[i]);
    }

    int k = 0;
    std::cin >> k;

    std::vector<std::pair<int, int>> vvv(k);

    for (int i = 0; i < k; i += 1) {
        int left = 0, right = 0;
        std::cin >> left >> right;
        vvv[i] = segtree->getMax(left - 1, right);
    }

    for (auto& elem : vvv) {
        std::cout << elem.second << ' ';
    }

    return 0;
}