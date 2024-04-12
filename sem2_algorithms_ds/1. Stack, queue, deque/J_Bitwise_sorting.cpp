#include <iostream>
#include <vector>
#include <queue>

void my_reverse(std::vector<int>& v, int i, int j) {
    if (j > 0) {
        --j;
    }
    else {
        return;
    }
    for (; i < j; ++i, --j) {
        std::swap(v[i], v[j]);
    }
}


int main() {
    int n = 0;
    std::cin >> n;

    std::vector<int> vec(n);
    for (int i = 0; i < vec.size(); ++i) {
        std::cin >> vec[i];
    }

    std::vector<std::queue<int> > vec_q(256);
    for (int k = 0; k < 4; ++k) {
        for (int idx = 0; idx < vec.size(); ++idx) {
            int byte = (vec[idx] >> (8 * k)) & 255;
            vec_q[byte].push(vec[idx]);
        }

        int i = 0;
        for (int j = 0; j < 256; ++j) {
            while (!vec_q[j].empty()) {
                vec[i] = vec_q[j].front();
                vec_q[j].pop();
                ++i;
            }
        }
    }

    int idxNegNum = vec.size();
    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] < 0) {
            idxNegNum = i;
            break;
        }
    }

    my_reverse(vec, 0, idxNegNum);
    my_reverse(vec, idxNegNum, vec.size());
    my_reverse(vec, 0, vec.size());


    for (const int& elem : vec) {
        std::cout << elem << ' ';
    }