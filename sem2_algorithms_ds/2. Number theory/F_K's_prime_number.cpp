#include <iostream>
#include <vector>

unsigned long long gcd(unsigned long long a, unsigned long long b) {
    return (b == 0) ? a : gcd(b, a % b);
}

bool hasThreePrimeDivisors(int n) {
    int cnt = 0;
    const int num = n;
    for (int i = 2; i * i <= n; i += 1) {
        if (n % i == 0) {
            cnt++;
            if (cnt >= 3) {
                return true;
            }
            while (n % i == 0) {
                n /= i;
            }

        }
    }
    if (n != 1) {
        cnt++;
        return (cnt >= 3);
    }
    return false;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    const int32_t size = 1299709;

    int n = 0;
    std::cin >> n;

    std::vector<bool> prime_numbers(size + 1, true);
    prime_numbers[0] = false;
    prime_numbers[1] = false;

    for (int i = 2; i * i <= size; i += 1) {
        if (prime_numbers[i]) {
            for (int j = i * i; j <= size; j += i) {
                prime_numbers[j] = false;
            }
        }
    }

    std::vector<int> prime;
    for (int i = 2; i <= size; ++i) {
        if (prime_numbers[i]) {
            prime.push_back(i);
        }
    }


    for (int i = 0; i < n; i += 1) {
        int a = 0;
        std::cin >> a;
        std::cout << prime[a - 1] << ' ';

    }

}