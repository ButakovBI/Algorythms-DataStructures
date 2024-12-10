#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

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

    int n = 0;
    std::cin >> n;

    std::vector<unsigned long long> prime_numbers(n + 1, 0);
    prime_numbers[0] = 1;
    prime_numbers[1] = 1;

    for (unsigned long long i = 2; i <= n; i += 1) {
        if (prime_numbers[i] == 0) {
            for (unsigned long long j = i * i; j <= n; j += i) {
                if (prime_numbers[j] == 0) {
                    prime_numbers[j] = i;
                }
            }
            prime_numbers[i] = i;
        }

    }

    unsigned long long summ = 0;

    for (unsigned long long i = 2; i <= n; i += 1) {
        summ += prime_numbers[i];
    }

    std::cout << summ;

}