#include <iostream>
#include <vector>

struct Node {
    Node* left_node = nullptr;
    Node* right_node = nullptr;
    size_t left_bound = 0;
    size_t right_bound = 0;

    static const int inf = 2147483647;

    int sum = 0;
    int minn = inf;
    int maxx = -inf;

    Node(const size_t left_bound, const size_t right_bound) : left_bound(left_bound), right_bound(right_bound) {
        if (left_bound + 1 < right_bound) {
            size_t mid = (left_bound + right_bound) / 2;
            left_node = new Node(left_bound, mid);
            right_node = new Node(mid, right_bound);
        }
    }

    void add(const size_t index, const int value) {
        this->sum += value;
        this->minn = std::min(minn, value);
        this->maxx = std::max(maxx, value);
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

    int operator[] (const size_t index) const {
        return this->getSum(index, index + 1);
    }

    int operator[] (const std::pair <const size_t, const size_t>& p) const {
        return this->getSum(p.first, p.second);
    }

};

int main() {
    int n = 0, k = 0;
    std::cin >> n >> k;
    std::vector<int> vec(n);
    Node node(0, n);

    for (int i = 0; i < n; i += 1) {
        int a = 0;
        std::cin >> a;
        node.add(i, a);
    }

    for (int j = 0; j < n - k + 1; j += 1) {
        std::cout << node.getMin(j, j + k) << std::endl;
    }
    return 0;
}