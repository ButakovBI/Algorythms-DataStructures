#include <iostream>
#include <vector>

void build(std::vector<long long>& values, long long n, long long& size);
void upd(std::vector<long long>& values, long long idx, long long x);
long long sum(const std::vector<long long>& values, long long idx,
              long long start, long long end, long long l, long long r);

int main() {
    long long n = 0, m = 0;
    std::cin >> n >> m;
    long long size = 1;
    std::vector<long long> values;
    build(values, n, size);
    long long command = 0;
    long long l = 0, r = 0, idx = 0;
    long long x = 0;
    for (long long i = 0; i < m; i += 1) {
        std::cin >> command;
        if (command == 1) {
            std::cin >> l >> r;
            std::cout << sum(values, 1, 1, size, l, r) << '\n';
        } else if (command == 2) {
            std::cin >> idx >> x;
            upd(values, size + idx - 1, x);
        }
//        for (auto value : values) {
//            std::cout << value << ' ';
//        }
//        std::cout << '\n';
    }

    return 0;
}

void build(std::vector<long long>& values, long long n, long long& size) {
    while (size < n) {
        size *= 2;
    }
    values.assign(2 * size, 0);
}

void upd(std::vector<long long>& values, long long idx, long long x) {
    values[idx] = x;
    for (idx /= 2; idx > 0; idx /= 2) {
        values[idx] = values[2 * idx] + values[2 * idx + 1];
    }
}

long long sum(const std::vector<long long>& values, long long idx, long long start, long long end, long long l, long long r) {
    if (start == l && end == r) {
        return values[idx];
    }
    if (l > r) {
        return 0;
    }
    long long mid = (start + end) / 2;
    long long res = 0;
    if (l <= mid) {
        res += sum(values, 2 * idx, start, mid, l, std::min(mid, r));
    }
    if (r >= mid + 1) {
        res += sum(values, 2 * idx + 1, mid + 1, end, std::max(mid + 1, l), r);

    }
//    std::cout << start << ' ' << mid << ' ' << end << " |idx " << idx << '\n';
    return res;
}


//5 9
//1 1 5
//2 4 3
//2 3 5
//1 4 4
//2 1 -6
//1 3 5
//1 1 1
//1 2 4
//1 1 2

//8 15
//2 1 1
//2 2 2
//2 3 5
//2 4 7
//2 5 0
//2 6 -1
//2 7 5
//2 8 3
//1 4 6
