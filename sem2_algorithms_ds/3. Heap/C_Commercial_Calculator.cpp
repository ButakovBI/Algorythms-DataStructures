#include <iostream>
#include <vector>
#include <iomanip>
#include <queue>

class Heap {

private:
    std::vector<int> vec;

    void SifhUp(int index) {
        if (index == 0) {
            return;
        }
        int p = (index - 1) / 2;
        if (vec[p] < vec[index]) {
            std::swap(vec[p], vec[index]);
            SifhUp(p);
        }
    }

    void SifhDown(int index) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        if (right > vec.size()) {
            return;
        }
        if (right == vec.size()) {
            right = left;
        }
        int imin = vec[left] > vec[right] ? left : right;
        if (vec[imin] < vec[index]) {
            std::swap(vec[imin], vec[index]);
            SifhDown(imin);
        }
    }

public:

    void add(int val) {
        vec.push_back(val);
        SifhUp(vec.size() - 1);
    }

    void clear() {
        vec.clear();
    }

    void extract() {
        if (vec.size() == 0) {
            std::cout << "CANNOT" << std::endl;
        }
        else {
            std::cout << vec[0] << std::endl;
            vec[0] = vec.back();
            vec.pop_back();
            SifhDown(0);

        }

    }

    bool empty() {
        return vec.size() == 0;
    }

    void pop_back() {
        while (!vec.empty()) {
            vec.pop_back();
        }
    }

    int get() {
        return vec.back();
    }

    void pop() {
        vec.pop_back();
    }

    int size() {
        return vec.size();
    }

};


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t = 0;
    std::cin >> t;

    std::priority_queue<int32_t, std::vector<int32_t>, std::greater<int32_t> > heap;

    for (int i = 0; i < t; ++i) {
        int a = 0;
        std::cin >> a;
        heap.push(a);
    }

    double ans = 0;
    int tmp = 0;
    while (heap.size() != 1) {
        tmp = heap.top();
        heap.pop();
        tmp += heap.top();
        heap.pop();
        ans += tmp;
        heap.push(tmp);
    }
    std::cout << std::fixed << std::setprecision(2) << ans * 0.05 << std::endl;

    return 0;
}