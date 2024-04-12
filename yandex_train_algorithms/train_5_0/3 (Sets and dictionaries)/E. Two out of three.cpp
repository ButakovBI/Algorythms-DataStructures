#include <iostream>
#include <set>
#include <unordered_set>

int main() {
    std::unordered_set<int> values;
    std::unordered_set<int> tmp;
    std::set<int> ans;

    int n1 = 0;
    std::cin >> n1;

    for (int i = 0; i < n1; i += 1) {
        int value = 0;
        std::cin >> value;
        values.insert(value);
    }

    int n2 = 0;
    std::cin >> n2;

    for (int i = 0; i < n2; i += 1) {
        int value = 0;
        std::cin >> value;
        if (values.find(value) != values.end()) {
            ans.insert(value);
        }
        tmp.insert(value);
    }
    for (auto& elem : tmp) {
        values.insert(elem);
    }

    int n3 = 0;
    std::cin >> n3;

    for (int i = 0; i < n3; i += 1) {
        int value = 0;
        std::cin >> value;
        if (values.find(value) != values.end()) {
            ans.insert(value);
        }
        tmp.insert(value);
    }

    for (auto& elem : ans) {
        std::cout << elem << ' ';
    }

    return 0;
}
