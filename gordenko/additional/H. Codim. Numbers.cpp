#include <iostream>
#include <queue>
#include <vector>

int cycle_shift_left(int number);
int cycle_shift_right(int number);
void dfs(std::vector<int>& lengths, std::vector<int>& used, std::vector<int>& path, std::queue<int>& q);


int main() {
    int first = 0, second = 0;
    std::cin >> first >> second;
    const int n = 10000;
    std::vector<int> used(n, false);
    std::vector<int> minimums(n, 1e9);
    std::vector<int> path(n, 1e9);
    minimums[first] = 0;
    path[first] = first;
    std::queue<int> q;
    q.push(first);
    dfs(minimums, used, path, q);

    std::vector<int> ans;
    while (path[second] != second) {
        ans.push_back(second);
        second = path[second];
    }
    ans.push_back(first);
//    for (auto& elem : ans) {
//        std::cout << elem << ' ';
//    }
    for (auto iter = ans.rbegin(); iter != ans.rend(); iter++) {
        std::cout << *iter << '\n';
    }
    return 0;
}

int cycle_shift_left(int number) {
    int first = number / 1000, second = (number % 1000) / 100, third = (number % 100) / 10, fourth = number % 10;
    return second * 1000 + third * 100 + fourth * 10 + first;
}

int cycle_shift_right(int number) {
    int first = number / 1000, second = (number % 1000) / 100, third = (number % 100) / 10, fourth = number % 10;
    return fourth * 1000 + first * 100 + second * 10 + third;
}

void dfs(std::vector<int>& lengths, std::vector<int>& used, std::vector<int>& path, std::queue<int>& q) {
    while (!q.empty()) {
        int number = q.front();

        q.pop();
        if (!used[number]) {
            if (number / 1000 != 9) {
                if (lengths[number + 1000] > lengths[number] + 1) {
                    lengths[number + 1000] = lengths[number] + 1;
                    path[number + 1000] = number;
                    q.push(number + 1000);
                }
            }
            if (number % 10 != 1) {
                if (lengths[number - 1] > lengths[number] + 1) {
                    lengths[number - 1] = lengths[number] + 1;
                    path[number - 1] = number;
                    q.push(number - 1);
                }
            }
            int tmp = cycle_shift_left(number);
            if (lengths[tmp] > lengths[number] + 1) {
                lengths[tmp] = lengths[number] + 1;
                path[tmp] = number;
                q.push(tmp);
            }
            tmp = cycle_shift_right(number);
            if (lengths[tmp] > lengths[number] + 1) {
                lengths[tmp] = lengths[number] + 1;
                path[tmp] = number;
                q.push(tmp);
            }
        }
    }
}