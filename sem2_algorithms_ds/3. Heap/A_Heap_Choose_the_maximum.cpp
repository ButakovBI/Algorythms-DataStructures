#include <iostream>
#include <vector>

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
        if (vec[imin] > vec[index]) {
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

};

int main() {

    std::string s = "";
    Heap heap;
    while (std::cin >> s) {
        if (s == "ADD") {
            int val = 0;
            std::cin >> val;
            heap.add(val);
        }
        else if (s == "CLEAR") {
            heap.clear();
        }
        else if (s == "EXTRACT") {
            heap.extract();
        }
    }
    return 0;
}