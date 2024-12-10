#include <iostream>
#include <vector>

long long binary_search_by_answer(std::vector<long long>& arr_prof, long long n, long long m);

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    long long t = 0;
    std::cin >> t;
    for (long long i = 0; i < t; i += 1) {
        long long n = 0, m = 0;
        std::cin >> n >> m;
        std::vector<long long> arr_prof(n, 0);
        long long prof = 0;
        for (long long j = 0; j < m; j += 1) {
            std::cin >> prof;
            arr_prof[prof - 1]++;

        }
        std::cout << binary_search_by_answer(arr_prof, n, m) << '\n';
    }

    return 0;
}

long long binary_search_by_answer(std::vector<long long>& arr_prof, long long n, long long m) {
    long long l = 0, r = 2 * m;
    while (l < r) {
        long long mid = (l + r) / 2;
        long long t = 0, task = 0;
        for (long long i = 0; i < n; i += 1) {
            if (arr_prof[i] <= mid) {
                t += (mid - arr_prof[i]) / 2;
            } else {
                task += arr_prof[i] - mid;
            }
        }
//        std::cout << t << ' ' << task << '\n';
        if (t >= task) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
//    std::cout  << '\n';

    return r;
}
