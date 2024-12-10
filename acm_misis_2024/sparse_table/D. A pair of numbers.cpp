#include <algorithm>
#include <iostream>
#include <vector>

int gcd(int a, int b);

int main() {
    int n = 0;
    std::cin >> n;

    std::vector<int> a(n);
    int log_n = 0;
    while ((1 << (log_n + 1)) <= n) {
        log_n++;
    }
    for (int i = 0; i < n; i += 1) {
        std::cin >> a[i];
    }
    std::vector<std::vector<int>> sparse_table1(n, std::vector<int>(log_n + 1)),
    sparse_table2(n, std::vector<int>(log_n + 1));
    int cnt_pairs = 0, max_j = 0, max_diff = 0;
    std::vector<int> left_idxs;
    std::vector<std::pair<int, int>> equal_idxs;
    std::vector<int> equal_idxs_gcd;
    for (int i = 0; i < n; i += 1) {
        sparse_table1[i][0] = a[i];
        sparse_table2[i][0] = a[i];
    }
    for (int j = 1; j <= log_n; j += 1) {
        for (int i = 0; i + (1 << j) - 1 < n; i += 1) {
            sparse_table1[i][j] = gcd(sparse_table1[i][j - 1], sparse_table1[i + (1 << (j - 1))][j - 1]);
            sparse_table2[i][j] = std::min(sparse_table2[i][j - 1], sparse_table2[i + (1 << (j - 1))][j - 1]);
            if (sparse_table1[i][j] == sparse_table2[i][j]) {
                equal_idxs.push_back({i, j});
                if (j > max_j) {
                    max_j = j;
                }
                equal_idxs_gcd.push_back(sparse_table1[i][j]);
            }
        }
    }
//    for (int i = 0; i < n; i += 1) {
//        for (int j = 1; j < log_n + 1; j += 1) {
//            std::cout << sparse_table2[i][j] << ' ';
//        }
//        std::cout << '\n';
//    }
//    std::cout << '\n';
//    for (int i = 0; i < equal_idxs_gcd.size(); i += 1) {
//        std::cout << equal_idxs[i].first << ' ' << equal_idxs[i].second << ' ' << equal_idxs_gcd[i] << '\n';
//    }
    max_diff = (1 << max_j) - 1;
    for (int i = 0; i < equal_idxs.size(); i += 1) {
        if (equal_idxs[i].second == max_j) {
//            std::cout << equal_idxs[i].first << ' ' << equal_idxs[i].second << ' ' << equal_idxs_gcd[i] << '\n';
            int cur_gcd = equal_idxs_gcd[i];
            int diff = (1 << max_j) - 1;
            for (int j = equal_idxs[i].first + (1 << max_j); j < n && j < equal_idxs[i].first + (1 << (max_j + 1)); j += 1) {
//                std::cout << max_diff << ' ' << diff << ' ' << a[j] << ' ' << cur_gcd << '\n';
                if (gcd(cur_gcd, a[j]) == cur_gcd) {
                    diff++;
                    if (max_diff < diff) {
                        max_diff = diff;
                        left_idxs.clear();
                        left_idxs.push_back(equal_idxs[i].first + 1);
                    } else if (max_diff == diff) {
                        left_idxs.push_back(equal_idxs[i].first + 1);
                    }
                }
            }
            if (diff == max_diff) {
                if (std::find(left_idxs.begin(), left_idxs.end(), equal_idxs[i].first + 1) == left_idxs.end()) {
                    left_idxs.push_back(equal_idxs[i].first + 1);
                }
            }
//            std::cout << diff << '\n';
        }
//        if (max_diff != 0 && cnt_pairs == 0) {
//            cnt_pairs = 1;
//            left_idxs.clear();
//            left_idxs.push_back(equal_idxs[equal_idxs_gcd.size() - 1].first + 1);
//        }
    }
    cnt_pairs = left_idxs.size();
    if (cnt_pairs == 0) {
        cnt_pairs = n;
        std::cout << cnt_pairs << ' ' << max_diff << '\n';
        for (int i = 0; i < cnt_pairs; i += 1) {
            std::cout << i + 1 << ' ';
        }
    } else {
        std::cout << cnt_pairs << ' ' << max_diff << '\n';
        for (int i = 0; i < cnt_pairs; i += 1) {
            std::cout << left_idxs[i] << ' ';
        }
    }


    return 0;
}

int gcd(int a, int b) {
    int tmp = 0;
    while (a != 0 && b != 0) {
        tmp = b;
        b = a % b;
        a = tmp;
    }
    return a + b;
}

//15
//5 3 9 6 12 3 6 2 4 8 10 4 6 3 3

//14
//5 3 9 6 12 3 6 2 4 8 10 6 3 3

//6
//2 3 3 6 3 9

//9
//2 4 3 3 6 3 9 2 2

